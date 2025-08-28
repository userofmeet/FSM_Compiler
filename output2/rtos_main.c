#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>

typedef enum {
    NAVIGATION_MOVING,
    NAVIGATION_ARRIVED,
    NAVIGATION_IDLE,
    NAVIGATION_AVOIDING_OBSTACLE,
    NAVIGATION_WAITING,
    NAVIGATION_ROUTE_PLANNING,
} Navigation_State;

Navigation_State current_state_Navigation = NAVIGATION_MOVING;

typedef enum {
    PAYLOADHANDLING_LOADING,
    PAYLOADHANDLING_IN_TRANSIT,
    PAYLOADHANDLING_DELIVERED,
    PAYLOADHANDLING_LOADED,
    PAYLOADHANDLING_UNLOADING,
    PAYLOADHANDLING_EMPTY,
} PayloadHandling_State;

PayloadHandling_State current_state_PayloadHandling = PAYLOADHANDLING_LOADING;

typedef enum {
    SAFETY_RECOVERY,
    SAFETY_EMERGENCY_STOP,
    SAFETY_HAZARD_DETECTED,
    SAFETY_OBSTACLE_ALERT,
    SAFETY_NORMAL,
    SAFETY_MANUAL_OVERRIDE,
} Safety_State;

Safety_State current_state_Safety = SAFETY_RECOVERY;

typedef enum {
    CONNECTIVITY_CONNECTING,
    CONNECTIVITY_LOST_SIGNAL,
    CONNECTIVITY_OFFLINE,
    CONNECTIVITY_CONNECTED,
    CONNECTIVITY_RECONNECTING,
} Connectivity_State;

Connectivity_State current_state_Connectivity = CONNECTIVITY_CONNECTING;

typedef enum {
    DIAGNOSTICS_RUNNING_CHECKS,
    DIAGNOSTICS_IDLE,
    DIAGNOSTICS_ERROR_DETECTED,
    DIAGNOSTICS_REPORTING,
    DIAGNOSTICS_MAINTENANCE,
} Diagnostics_State;

Diagnostics_State current_state_Diagnostics = DIAGNOSTICS_RUNNING_CHECKS;

typedef enum {
    USERINTERFACE_PROCESSING,
    USERINTERFACE_IDLE,
    USERINTERFACE_ALERT,
    USERINTERFACE_WAITING_INPUT,
    USERINTERFACE_DISPLAYING_FEEDBACK,
} UserInterface_State;

UserInterface_State current_state_UserInterface = USERINTERFACE_PROCESSING;

void task_Navigation(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Navigation, &event, portMAX_DELAY)) {
            switch (current_state_Navigation) {
                case NAVIGATION_MOVING:
                    if (strcmp(event, "detect_obstacle") == 0) current_state_Navigation = NAVIGATION_AVOIDING_OBSTACLE;
                    if (strcmp(event, "route_lost") == 0) current_state_Navigation = NAVIGATION_ROUTE_PLANNING;
                    if (strcmp(event, "wait_command") == 0) current_state_Navigation = NAVIGATION_WAITING;
                    if (strcmp(event, "reach_destination") == 0) current_state_Navigation = NAVIGATION_ARRIVED;
                    break;
                case NAVIGATION_ARRIVED:
                    if (strcmp(event, "continue") == 0) current_state_Navigation = NAVIGATION_IDLE;
                    break;
                case NAVIGATION_IDLE:
                    if (strcmp(event, "start_route") == 0) current_state_Navigation = NAVIGATION_ROUTE_PLANNING;
                    break;
                case NAVIGATION_AVOIDING_OBSTACLE:
                    if (strcmp(event, "obstacle_cleared") == 0) current_state_Navigation = NAVIGATION_MOVING;
                    break;
                case NAVIGATION_WAITING:
                    if (strcmp(event, "continue") == 0) current_state_Navigation = NAVIGATION_MOVING;
                    break;
                case NAVIGATION_ROUTE_PLANNING:
                    if (strcmp(event, "route_ready") == 0) current_state_Navigation = NAVIGATION_MOVING;
                    break;
            }
        }
    }
}

void task_PayloadHandling(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_PayloadHandling, &event, portMAX_DELAY)) {
            switch (current_state_PayloadHandling) {
                case PAYLOADHANDLING_LOADING:
                    if (strcmp(event, "fail") == 0) current_state_PayloadHandling = PAYLOADHANDLING_DELIVERED;
                    if (strcmp(event, "finish_loading") == 0) current_state_PayloadHandling = PAYLOADHANDLING_LOADED;
                    break;
                case PAYLOADHANDLING_IN_TRANSIT:
                    if (strcmp(event, "begin_unloading") == 0) current_state_PayloadHandling = PAYLOADHANDLING_UNLOADING;
                    break;
                case PAYLOADHANDLING_DELIVERED:
                    if (strcmp(event, "finish_unloading") == 0) current_state_PayloadHandling = PAYLOADHANDLING_EMPTY;
                    break;
                case PAYLOADHANDLING_LOADED:
                    if (strcmp(event, "start_transit") == 0) current_state_PayloadHandling = PAYLOADHANDLING_IN_TRANSIT;
                    break;
                case PAYLOADHANDLING_UNLOADING:
                    if (strcmp(event, "finish_unloading") == 0) current_state_PayloadHandling = PAYLOADHANDLING_DELIVERED;
                    if (strcmp(event, "fail") == 0) current_state_PayloadHandling = PAYLOADHANDLING_DELIVERED;
                    break;
                case PAYLOADHANDLING_EMPTY:
                    if (strcmp(event, "begin_loading") == 0) current_state_PayloadHandling = PAYLOADHANDLING_LOADING;
                    break;
            }
        }
    }
}

void task_Safety(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Safety, &event, portMAX_DELAY)) {
            switch (current_state_Safety) {
                case SAFETY_RECOVERY:
                    if (strcmp(event, "resume") == 0) current_state_Safety = SAFETY_NORMAL;
                    break;
                case SAFETY_EMERGENCY_STOP:
                    if (strcmp(event, "reset") == 0) current_state_Safety = SAFETY_RECOVERY;
                    break;
                case SAFETY_HAZARD_DETECTED:
                    if (strcmp(event, "emergency_stop") == 0) current_state_Safety = SAFETY_EMERGENCY_STOP;
                    break;
                case SAFETY_OBSTACLE_ALERT:
                    if (strcmp(event, "resume") == 0) current_state_Safety = SAFETY_NORMAL;
                    if (strcmp(event, "emergency_stop") == 0) current_state_Safety = SAFETY_EMERGENCY_STOP;
                    break;
                case SAFETY_NORMAL:
                    if (strcmp(event, "hazard") == 0) current_state_Safety = SAFETY_HAZARD_DETECTED;
                    if (strcmp(event, "override") == 0) current_state_Safety = SAFETY_MANUAL_OVERRIDE;
                    if (strcmp(event, "detect_obstacle") == 0) current_state_Safety = SAFETY_OBSTACLE_ALERT;
                    if (strcmp(event, "emergency_stop") == 0) current_state_Safety = SAFETY_EMERGENCY_STOP;
                    break;
                case SAFETY_MANUAL_OVERRIDE:
                    if (strcmp(event, "reset") == 0) current_state_Safety = SAFETY_NORMAL;
                    break;
            }
        }
    }
}

void task_Connectivity(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Connectivity, &event, portMAX_DELAY)) {
            switch (current_state_Connectivity) {
                case CONNECTIVITY_CONNECTING:
                    if (strcmp(event, "establish_link") == 0) current_state_Connectivity = CONNECTIVITY_CONNECTED;
                    break;
                case CONNECTIVITY_LOST_SIGNAL:
                    if (strcmp(event, "attempt_reconnect") == 0) current_state_Connectivity = CONNECTIVITY_RECONNECTING;
                    break;
                case CONNECTIVITY_OFFLINE:
                    if (strcmp(event, "power_on") == 0) current_state_Connectivity = CONNECTIVITY_CONNECTING;
                    break;
                case CONNECTIVITY_CONNECTED:
                    if (strcmp(event, "lose_link") == 0) current_state_Connectivity = CONNECTIVITY_LOST_SIGNAL;
                    break;
                case CONNECTIVITY_RECONNECTING:
                    if (strcmp(event, "link_restored") == 0) current_state_Connectivity = CONNECTIVITY_CONNECTED;
                    if (strcmp(event, "lose_link") == 0) current_state_Connectivity = CONNECTIVITY_OFFLINE;
                    break;
            }
        }
    }
}

void task_Diagnostics(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Diagnostics, &event, portMAX_DELAY)) {
            switch (current_state_Diagnostics) {
                case DIAGNOSTICS_RUNNING_CHECKS:
                    if (strcmp(event, "detect_error") == 0) current_state_Diagnostics = DIAGNOSTICS_ERROR_DETECTED;
                    if (strcmp(event, "resolve") == 0) current_state_Diagnostics = DIAGNOSTICS_IDLE;
                    break;
                case DIAGNOSTICS_IDLE:
                    if (strcmp(event, "initiate_check") == 0) current_state_Diagnostics = DIAGNOSTICS_RUNNING_CHECKS;
                    break;
                case DIAGNOSTICS_ERROR_DETECTED:
                    if (strcmp(event, "report") == 0) current_state_Diagnostics = DIAGNOSTICS_REPORTING;
                    break;
                case DIAGNOSTICS_REPORTING:
                    if (strcmp(event, "schedule_maintenance") == 0) current_state_Diagnostics = DIAGNOSTICS_MAINTENANCE;
                    break;
                case DIAGNOSTICS_MAINTENANCE:
                    if (strcmp(event, "resolve") == 0) current_state_Diagnostics = DIAGNOSTICS_IDLE;
                    break;
            }
        }
    }
}

void task_UserInterface(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_UserInterface, &event, portMAX_DELAY)) {
            switch (current_state_UserInterface) {
                case USERINTERFACE_PROCESSING:
                    if (strcmp(event, "feedback") == 0) current_state_UserInterface = USERINTERFACE_DISPLAYING_FEEDBACK;
                    break;
                case USERINTERFACE_IDLE:
                    if (strcmp(event, "receive_input") == 0) current_state_UserInterface = USERINTERFACE_WAITING_INPUT;
                    break;
                case USERINTERFACE_ALERT:
                    break;
                case USERINTERFACE_WAITING_INPUT:
                    if (strcmp(event, "process") == 0) current_state_UserInterface = USERINTERFACE_PROCESSING;
                    break;
                case USERINTERFACE_DISPLAYING_FEEDBACK:
                    if (strcmp(event, "timeout") == 0) current_state_UserInterface = USERINTERFACE_IDLE;
                    break;
            }
        }
    }
}

QueueHandle_t queue_Navigation;
QueueHandle_t queue_PayloadHandling;
QueueHandle_t queue_Safety;
QueueHandle_t queue_Connectivity;
QueueHandle_t queue_Diagnostics;
QueueHandle_t queue_UserInterface;

int main() {
    queue_Navigation = xQueueCreate(10, sizeof(char[32]));
    queue_PayloadHandling = xQueueCreate(10, sizeof(char[32]));
    queue_Safety = xQueueCreate(10, sizeof(char[32]));
    queue_Connectivity = xQueueCreate(10, sizeof(char[32]));
    queue_Diagnostics = xQueueCreate(10, sizeof(char[32]));
    queue_UserInterface = xQueueCreate(10, sizeof(char[32]));
    xTaskCreate(task_Navigation, "Navigation", 1000, NULL, 2, NULL);
    xTaskCreate(task_PayloadHandling, "PayloadHandling", 1000, NULL, 2, NULL);
    xTaskCreate(task_Safety, "Safety", 1000, NULL, 2, NULL);
    xTaskCreate(task_Connectivity, "Connectivity", 1000, NULL, 2, NULL);
    xTaskCreate(task_Diagnostics, "Diagnostics", 1000, NULL, 2, NULL);
    xTaskCreate(task_UserInterface, "UserInterface", 1000, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}
