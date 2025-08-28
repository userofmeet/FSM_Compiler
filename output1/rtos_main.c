#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

/* =========================
 * Enums (your states)
 * ========================= */

typedef enum {
    NAVIGATION_TAKEOFF,
    NAVIGATION_DESCENDING,
    NAVIGATION_ASCENDING,
    NAVIGATION_LANDING,
    NAVIGATION_HOLDING,
    NAVIGATION_CRUISE,
    NAVIGATION_IDLE,
} Navigation_State;

typedef enum {
    CAMERA_CAM_IDLE,
    CAMERA_RECORDING,
    CAMERA_STREAMING,
    CAMERA_SNAPSHOT,
    CAMERA_OFF,
} Camera_State;

typedef enum {
    COMMUNICATION_CONNECTING,
    COMMUNICATION_CONNECTED,
    COMMUNICATION_ERROR,
    COMMUNICATION_DISCONNECTED,
    COMMUNICATION_DEGRADED,
} Communication_State;

typedef enum {
    OBSTACLEAVOIDANCE_OVERRIDE,
    OBSTACLEAVOIDANCE_PATH_RECOVERED,
    OBSTACLEAVOIDANCE_EVADING,
    OBSTACLEAVOIDANCE_OBSTACLE_DETECTED,
    OBSTACLEAVOIDANCE_STUCK,
    OBSTACLEAVOIDANCE_CLEAR_PATH,
} ObstacleAvoidance_State;

typedef enum {
    LOCALIZATION_LOST_FIX,
    LOCALIZATION_SEARCHING,
    LOCALIZATION_REACQUIRING,
    LOCALIZATION_LOCKED,
    LOCALIZATION_UNAVAILABLE,
} Localization_State;

typedef enum {
    BATTERY_LOW,
    BATTERY_FULL,
    BATTERY_DISCHARGING,
    BATTERY_CHARGING,
    BATTERY_CRITICAL,
    BATTERY_SHUTDOWN,
} Battery_State;

typedef enum {
    MISSIONCONTROL_READY,
    MISSIONCONTROL_PLANNING,
    MISSIONCONTROL_PAUSED,
    MISSIONCONTROL_IN_PROGRESS,
    MISSIONCONTROL_COMPLETED,
    MISSIONCONTROL_ABORTED,
} MissionControl_State;

/* =========================
 * Global current states
 * ========================= */
Navigation_State        current_state_Navigation       = NAVIGATION_TAKEOFF;
Camera_State            current_state_Camera           = CAMERA_CAM_IDLE;
Communication_State     current_state_Communication    = COMMUNICATION_CONNECTING;
ObstacleAvoidance_State current_state_ObstacleAvoidance= OBSTACLEAVOIDANCE_OVERRIDE;
Localization_State      current_state_Localization     = LOCALIZATION_LOST_FIX;
Battery_State           current_state_Battery          = BATTERY_LOW;
MissionControl_State    current_state_MissionControl   = MISSIONCONTROL_READY;

/* =========================
 * Queues
 * ========================= */
QueueHandle_t queue_Navigation;
QueueHandle_t queue_Camera;
QueueHandle_t queue_Communication;
QueueHandle_t queue_ObstacleAvoidance;
QueueHandle_t queue_Localization;
QueueHandle_t queue_Battery;
QueueHandle_t queue_MissionControl;

/* =========================
 * Logging helpers
 * ========================= */
static const char *TAG_NAV = "NAV";
static const char *TAG_CAM = "CAM";
static const char *TAG_COM = "COM";
static const char *TAG_OA  = "OA";
static const char *TAG_LOC = "LOC";
static const char *TAG_BAT = "BAT";
static const char *TAG_MIS = "MIS";
static const char *TAG_DEMO= "DEMO";

/* name lookup tables for pretty logs */
static const char* nav_name(Navigation_State s){
    switch(s){
        case NAVIGATION_TAKEOFF: return "TAKEOFF";
        case NAVIGATION_DESCENDING: return "DESCENDING";
        case NAVIGATION_ASCENDING: return "ASCENDING";
        case NAVIGATION_LANDING: return "LANDING";
        case NAVIGATION_HOLDING: return "HOLDING";
        case NAVIGATION_CRUISE: return "CRUISE";
        case NAVIGATION_IDLE: return "IDLE";
        default: return "?";
    }
}
static const char* cam_name(Camera_State s){
    switch(s){
        case CAMERA_CAM_IDLE: return "IDLE";
        case CAMERA_RECORDING: return "RECORDING";
        case CAMERA_STREAMING: return "STREAMING";
        case CAMERA_SNAPSHOT: return "SNAPSHOT";
        case CAMERA_OFF: return "OFF";
        default: return "?";
    }
}
static const char* com_name(Communication_State s){
    switch(s){
        case COMMUNICATION_CONNECTING: return "CONNECTING";
        case COMMUNICATION_CONNECTED: return "CONNECTED";
        case COMMUNICATION_ERROR: return "ERROR";
        case COMMUNICATION_DISCONNECTED: return "DISCONNECTED";
        case COMMUNICATION_DEGRADED: return "DEGRADED";
        default: return "?";
    }
}
static const char* oa_name(ObstacleAvoidance_State s){
    switch(s){
        case OBSTACLEAVOIDANCE_OVERRIDE: return "OVERRIDE";
        case OBSTACLEAVOIDANCE_PATH_RECOVERED: return "PATH_RECOVERED";
        case OBSTACLEAVOIDANCE_EVADING: return "EVADING";
        case OBSTACLEAVOIDANCE_OBSTACLE_DETECTED: return "OBSTACLE_DETECTED";
        case OBSTACLEAVOIDANCE_STUCK: return "STUCK";
        case OBSTACLEAVOIDANCE_CLEAR_PATH: return "CLEAR_PATH";
        default: return "?";
    }
}
static const char* loc_name(Localization_State s){
    switch(s){
        case LOCALIZATION_LOST_FIX: return "LOST_FIX";
        case LOCALIZATION_SEARCHING: return "SEARCHING";
        case LOCALIZATION_REACQUIRING: return "REACQUIRING";
        case LOCALIZATION_LOCKED: return "LOCKED";
        case LOCALIZATION_UNAVAILABLE: return "UNAVAILABLE";
        default: return "?";
    }
}
static const char* bat_name(Battery_State s){
    switch(s){
        case BATTERY_LOW: return "LOW";
        case BATTERY_FULL: return "FULL";
        case BATTERY_DISCHARGING: return "DISCHARGING";
        case BATTERY_CHARGING: return "CHARGING";
        case BATTERY_CRITICAL: return "CRITICAL";
        case BATTERY_SHUTDOWN: return "SHUTDOWN";
        default: return "?";
    }
}
static const char* mis_name(MissionControl_State s){
    switch(s){
        case MISSIONCONTROL_READY: return "READY";
        case MISSIONCONTROL_PLANNING: return "PLANNING";
        case MISSIONCONTROL_PAUSED: return "PAUSED";
        case MISSIONCONTROL_IN_PROGRESS: return "IN_PROGRESS";
        case MISSIONCONTROL_COMPLETED: return "COMPLETED";
        case MISSIONCONTROL_ABORTED: return "ABORTED";
        default: return "?";
    }
}

/* small helper: send string event into a queue */
static void send_event(QueueHandle_t q, const char *s){
    char event[32] = {0};
    strncpy(event, s, sizeof(event)-1);
    xQueueSend(q, &event, 0);
}

/* =========================
 * Tasks (your logic + logs)
 * ========================= */

void task_Navigation(void *params) {
    char event[32];
    ESP_LOGI(TAG_NAV, "Initial: %s", nav_name(current_state_Navigation));
    while (1) {
        if (xQueueReceive(queue_Navigation, &event, portMAX_DELAY)) {
            Navigation_State prev = current_state_Navigation;
            switch (current_state_Navigation) {
                case NAVIGATION_TAKEOFF:
                    if (strcmp(event, "reach_altitude") == 0) current_state_Navigation = NAVIGATION_ASCENDING;
                    break;
                case NAVIGATION_DESCENDING:
                    if (strcmp(event, "begin_landing") == 0) current_state_Navigation = NAVIGATION_LANDING;
                    break;
                case NAVIGATION_ASCENDING:
                    if (strcmp(event, "reach_altitude") == 0) current_state_Navigation = NAVIGATION_CRUISE;
                    break;
                case NAVIGATION_LANDING:
                    if (strcmp(event, "landed") == 0) current_state_Navigation = NAVIGATION_IDLE;
                    break;
                case NAVIGATION_HOLDING:
                    if (strcmp(event, "resume_cruise") == 0) current_state_Navigation = NAVIGATION_CRUISE;
                    break;
                case NAVIGATION_CRUISE:
                    if (strcmp(event, "begin_descent") == 0) current_state_Navigation = NAVIGATION_DESCENDING;
                    if (strcmp(event, "hold_position") == 0) current_state_Navigation = NAVIGATION_HOLDING;
                    if (strcmp(event, "emergency") == 0) current_state_Navigation = NAVIGATION_DESCENDING;
                    break;
                case NAVIGATION_IDLE:
                    if (strcmp(event, "start_mission") == 0) current_state_Navigation = NAVIGATION_TAKEOFF;
                    break;
            }
            if (prev != current_state_Navigation) {
                ESP_LOGI(TAG_NAV, "Event '%s' => %s", event, nav_name(current_state_Navigation));
            }
        }
    }
}

void task_Camera(void *params) {
    char event[32];
    ESP_LOGI(TAG_CAM, "Initial: %s", cam_name(current_state_Camera));
    while (1) {
        if (xQueueReceive(queue_Camera, &event, portMAX_DELAY)) {
            Camera_State prev = current_state_Camera;
            switch (current_state_Camera) {
                case CAMERA_CAM_IDLE:
                    if (strcmp(event, "start_record") == 0) current_state_Camera = CAMERA_RECORDING;
                    if (strcmp(event, "shutdown") == 0) current_state_Camera = CAMERA_OFF;
                    if (strcmp(event, "start_stream") == 0) current_state_Camera = CAMERA_STREAMING;
                    if (strcmp(event, "take_photo") == 0) current_state_Camera = CAMERA_SNAPSHOT;
                    break;
                case CAMERA_RECORDING:
                    if (strcmp(event, "stop") == 0) current_state_Camera = CAMERA_CAM_IDLE;
                    if (strcmp(event, "take_photo") == 0) current_state_Camera = CAMERA_SNAPSHOT;
                    if (strcmp(event, "pause") == 0) current_state_Camera = CAMERA_SNAPSHOT;
                    break;
                case CAMERA_STREAMING:
                    if (strcmp(event, "stop") == 0) current_state_Camera = CAMERA_CAM_IDLE;
                    break;
                case CAMERA_SNAPSHOT:
                    if (strcmp(event, "resume") == 0) current_state_Camera = CAMERA_RECORDING;
                    break;
                case CAMERA_OFF:
                    break;
            }
            if (prev != current_state_Camera) {
                ESP_LOGI(TAG_CAM, "Event '%s' => %s", event, cam_name(current_state_Camera));
            }
        }
    }
}

void task_Communication(void *params) {
    char event[32];
    ESP_LOGI(TAG_COM, "Initial: %s", com_name(current_state_Communication));
    while (1) {
        if (xQueueReceive(queue_Communication, &event, portMAX_DELAY)) {
            Communication_State prev = current_state_Communication;
            switch (current_state_Communication) {
                case COMMUNICATION_CONNECTING:
                    if (strcmp(event, "fail") == 0) current_state_Communication = COMMUNICATION_DISCONNECTED;
                    if (strcmp(event, "success") == 0) current_state_Communication = COMMUNICATION_CONNECTED;
                    break;
                case COMMUNICATION_CONNECTED:
                    if (strcmp(event, "degrade") == 0) current_state_Communication = COMMUNICATION_DEGRADED;
                    if (strcmp(event, "lost_connection") == 0) current_state_Communication = COMMUNICATION_CONNECTING;
                    break;
                case COMMUNICATION_ERROR:
                    if (strcmp(event, "retry") == 0) current_state_Communication = COMMUNICATION_DISCONNECTED;
                    break;
                case COMMUNICATION_DISCONNECTED:
                    if (strcmp(event, "fail") == 0) current_state_Communication = COMMUNICATION_ERROR;
                    if (strcmp(event, "initiate") == 0) current_state_Communication = COMMUNICATION_CONNECTING;
                    break;
                case COMMUNICATION_DEGRADED:
                    if (strcmp(event, "recover") == 0) current_state_Communication = COMMUNICATION_CONNECTED;
                    if (strcmp(event, "lost_connection") == 0) current_state_Communication = COMMUNICATION_CONNECTING;
                    break;
            }
            if (prev != current_state_Communication) {
                ESP_LOGI(TAG_COM, "Event '%s' => %s", event, com_name(current_state_Communication));
            }
        }
    }
}

void task_ObstacleAvoidance(void *params) {
    char event[32];
    ESP_LOGI(TAG_OA, "Initial: %s", oa_name(current_state_ObstacleAvoidance));
    while (1) {
        if (xQueueReceive(queue_ObstacleAvoidance, &event, portMAX_DELAY)) {
            ObstacleAvoidance_State prev = current_state_ObstacleAvoidance;
            switch (current_state_ObstacleAvoidance) {
                case OBSTACLEAVOIDANCE_OVERRIDE:
                    if (strcmp(event, "manual_clear") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_PATH_RECOVERED;
                    break;
                case OBSTACLEAVOIDANCE_PATH_RECOVERED:
                    if (strcmp(event, "recover") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_CLEAR_PATH;
                    if (strcmp(event, "detect") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_OBSTACLE_DETECTED;
                    break;
                case OBSTACLEAVOIDANCE_EVADING:
                    if (strcmp(event, "recover") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_PATH_RECOVERED;
                    if (strcmp(event, "stuck") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_STUCK;
                    break;
                case OBSTACLEAVOIDANCE_OBSTACLE_DETECTED:
                    if (strcmp(event, "evade") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_EVADING;
                    break;
                case OBSTACLEAVOIDANCE_STUCK:
                    if (strcmp(event, "override") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_OVERRIDE;
                    break;
                case OBSTACLEAVOIDANCE_CLEAR_PATH:
                    if (strcmp(event, "detect") == 0) current_state_ObstacleAvoidance = OBSTACLEAVOIDANCE_OBSTACLE_DETECTED;
                    break;
            }
            if (prev != current_state_ObstacleAvoidance) {
                ESP_LOGI(TAG_OA, "Event '%s' => %s", event, oa_name(current_state_ObstacleAvoidance));
            }
        }
    }
}

void task_Localization(void *params) {
    char event[32];
    ESP_LOGI(TAG_LOC, "Initial: %s", loc_name(current_state_Localization));
    while (1) {
        if (xQueueReceive(queue_Localization, &event, portMAX_DELAY)) {
            Localization_State prev = current_state_Localization;
            switch (current_state_Localization) {
                case LOCALIZATION_LOST_FIX:
                    if (strcmp(event, "reacquire") == 0) current_state_Localization = LOCALIZATION_REACQUIRING;
                    break;
                case LOCALIZATION_SEARCHING:
                    if (strcmp(event, "gps_fix") == 0) current_state_Localization = LOCALIZATION_LOCKED;
                    break;
                case LOCALIZATION_REACQUIRING:
                    if (strcmp(event, "lose_fix") == 0) current_state_Localization = LOCALIZATION_LOST_FIX;
                    if (strcmp(event, "gps_fix") == 0) current_state_Localization = LOCALIZATION_LOCKED;
                    break;
                case LOCALIZATION_LOCKED:
                    if (strcmp(event, "drift_detected") == 0) current_state_Localization = LOCALIZATION_SEARCHING;
                    if (strcmp(event, "lose_fix") == 0) current_state_Localization = LOCALIZATION_LOST_FIX;
                    break;
                case LOCALIZATION_UNAVAILABLE:
                    if (strcmp(event, "start_search") == 0) current_state_Localization = LOCALIZATION_SEARCHING;
                    break;
            }
            if (prev != current_state_Localization) {
                ESP_LOGI(TAG_LOC, "Event '%s' => %s", event, loc_name(current_state_Localization));
            }
        }
    }
}

void task_Battery(void *params) {
    char event[32];
    ESP_LOGI(TAG_BAT, "Initial: %s", bat_name(current_state_Battery));
    while (1) {
        if (xQueueReceive(queue_Battery, &event, portMAX_DELAY)) {
            Battery_State prev = current_state_Battery;
            switch (current_state_Battery) {
                case BATTERY_LOW:
                    if (strcmp(event, "plug_in") == 0) current_state_Battery = BATTERY_CHARGING;
                    if (strcmp(event, "alert_critical") == 0) current_state_Battery = BATTERY_CRITICAL;
                    break;
                case BATTERY_FULL:
                    if (strcmp(event, "unplug") == 0) current_state_Battery = BATTERY_DISCHARGING;
                    break;
                case BATTERY_DISCHARGING:
                    if (strcmp(event, "alert_low") == 0) current_state_Battery = BATTERY_LOW;
                    if (strcmp(event, "plug_in") == 0) current_state_Battery = BATTERY_CHARGING;
                    break;
                case BATTERY_CHARGING:
                    if (strcmp(event, "charge") == 0) current_state_Battery = BATTERY_FULL;
                    break;
                case BATTERY_CRITICAL:
                    if (strcmp(event, "power_off") == 0) current_state_Battery = BATTERY_SHUTDOWN;
                    if (strcmp(event, "plug_in") == 0) current_state_Battery = BATTERY_CHARGING;
                    break;
                case BATTERY_SHUTDOWN:
                    break;
            }
            if (prev != current_state_Battery) {
                ESP_LOGI(TAG_BAT, "Event '%s' => %s", event, bat_name(current_state_Battery));
            }
        }
    }
}

void task_MissionControl(void *params) {
    char event[32];
    ESP_LOGI(TAG_MIS, "Initial: %s", mis_name(current_state_MissionControl));
    while (1) {
        if (xQueueReceive(queue_MissionControl, &event, portMAX_DELAY)) {
            MissionControl_State prev = current_state_MissionControl;
            switch (current_state_MissionControl) {
                case MISSIONCONTROL_READY:
                    if (strcmp(event, "start") == 0) current_state_MissionControl = MISSIONCONTROL_IN_PROGRESS;
                    break;
                case MISSIONCONTROL_PLANNING:
                    if (strcmp(event, "plan_ready") == 0) current_state_MissionControl = MISSIONCONTROL_READY;
                    break;
                case MISSIONCONTROL_PAUSED:
                    if (strcmp(event, "abort") == 0) current_state_MissionControl = MISSIONCONTROL_ABORTED;
                    if (strcmp(event, "resume") == 0) current_state_MissionControl = MISSIONCONTROL_IN_PROGRESS;
                    break;
                case MISSIONCONTROL_IN_PROGRESS:
                    if (strcmp(event, "complete") == 0) current_state_MissionControl = MISSIONCONTROL_COMPLETED;
                    if (strcmp(event, "pause") == 0) current_state_MissionControl = MISSIONCONTROL_PAUSED;
                    if (strcmp(event, "abort") == 0) current_state_MissionControl = MISSIONCONTROL_ABORTED;
                    break;
                case MISSIONCONTROL_COMPLETED:
                    break;
                case MISSIONCONTROL_ABORTED:
                    if (strcmp(event, "plan_ready") == 0) current_state_MissionControl = MISSIONCONTROL_PLANNING;
                    break;
            }
            if (prev != current_state_MissionControl) {
                ESP_LOGI(TAG_MIS, "Event '%s' => %s", event, mis_name(current_state_MissionControl));
            }
        }
    }
}

/* ===========================================
 * Demo task to feed some example events
 * =========================================== */
static void task_EventFeeder(void *param){
    vTaskDelay(pdMS_TO_TICKS(1000));
    ESP_LOGI(TAG_DEMO, "Feeding demo events...");

    // Mission starts
    send_event(queue_MissionControl, "start");
    send_event(queue_Navigation, "reach_altitude"); // TAKEOFF -> ASCENDING
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Navigation, "reach_altitude"); // ASCENDING -> CRUISE
    send_event(queue_Camera, "start_record");
    send_event(queue_Communication, "success");     // CONNECTING -> CONNECTED
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_ObstacleAvoidance, "detect");
    send_event(queue_ObstacleAvoidance, "evade");
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_ObstacleAvoidance, "recover"); // EVADING -> PATH_RECOVERED
    send_event(queue_Localization, "reacquire");    // LOST_FIX -> REACQUIRING
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Localization, "gps_fix");      // -> LOCKED
    send_event(queue_Battery, "plug_in");           // LOW -> CHARGING (demo)
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Navigation, "hold_position");  // CRUISE -> HOLDING
    send_event(queue_Camera, "take_photo");         // RECORDING -> SNAPSHOT
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Camera, "resume");             // SNAPSHOT -> RECORDING
    send_event(queue_Navigation, "resume_cruise");  // HOLDING -> CRUISE
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Navigation, "begin_descent");  // CRUISE -> DESCENDING
    send_event(queue_Navigation, "begin_landing");  // DESCENDING -> LANDING
    vTaskDelay(pdMS_TO_TICKS(500));

    send_event(queue_Navigation, "landed");         // LANDING -> IDLE
    send_event(queue_MissionControl, "complete");   // IN_PROGRESS -> COMPLETED

    ESP_LOGI(TAG_DEMO, "Demo sequence done.");
    vTaskDelete(NULL);
}

/* =========================
 * app_main (ESP-IDF entry)
 * ========================= */
void app_main(void)
{
    /* Create queues. Each item is a 32-char array (copied by value). */
    queue_Navigation        = xQueueCreate(10, sizeof(char[32]));
    queue_Camera            = xQueueCreate(10, sizeof(char[32]));
    queue_Communication     = xQueueCreate(10, sizeof(char[32]));
    queue_ObstacleAvoidance = xQueueCreate(10, sizeof(char[32]));
    queue_Localization      = xQueueCreate(10, sizeof(char[32]));
    queue_Battery           = xQueueCreate(10, sizeof(char[32]));
    queue_MissionControl    = xQueueCreate(10, sizeof(char[32]));

    configASSERT(queue_Navigation && queue_Camera && queue_Communication &&
                 queue_ObstacleAvoidance && queue_Localization &&
                 queue_Battery && queue_MissionControl);

    /* Create tasks. Stack depth is in words, not bytes. */
    const uint32_t STACK = 4096;  // generous for logging/string ops
    xTaskCreate(task_Navigation,        "Navigation",        STACK, NULL, 5, NULL);
    xTaskCreate(task_Camera,            "Camera",            STACK, NULL, 5, NULL);
    xTaskCreate(task_Communication,     "Communication",     STACK, NULL, 5, NULL);
    xTaskCreate(task_ObstacleAvoidance, "ObstacleAvoidance", STACK, NULL, 5, NULL);
    xTaskCreate(task_Localization,      "Localization",      STACK, NULL, 5, NULL);
    xTaskCreate(task_Battery,           "Battery",           STACK, NULL, 5, NULL);
    xTaskCreate(task_MissionControl,    "MissionControl",    STACK, NULL, 5, NULL);

    /* Demo event feeder so you see transitions on the serial monitor */
    xTaskCreate(task_EventFeeder,       "EventFeeder",       STACK, NULL, 4, NULL);
}
