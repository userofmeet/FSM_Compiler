#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>

extern void handle_event_Navigation(const char*);
extern void handle_event_Camera(const char*);
extern void handle_event_Communication(const char*);
extern void handle_event_ObstacleAvoidance(const char*);
extern void handle_event_Localization(const char*);
extern void handle_event_Battery(const char*);
extern void handle_event_MissionControl(const char*);

QueueHandle_t queue_Navigation;
QueueHandle_t queue_Camera;
QueueHandle_t queue_Communication;
QueueHandle_t queue_ObstacleAvoidance;
QueueHandle_t queue_Localization;
QueueHandle_t queue_Battery;
QueueHandle_t queue_MissionControl;

void task_Navigation(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Navigation, &event, portMAX_DELAY)) {
            handle_event_Navigation(event);
        }
    }
}

void task_Camera(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Camera, &event, portMAX_DELAY)) {
            handle_event_Camera(event);
        }
    }
}

void task_Communication(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Communication, &event, portMAX_DELAY)) {
            handle_event_Communication(event);
        }
    }
}

void task_ObstacleAvoidance(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_ObstacleAvoidance, &event, portMAX_DELAY)) {
            handle_event_ObstacleAvoidance(event);
        }
    }
}

void task_Localization(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Localization, &event, portMAX_DELAY)) {
            handle_event_Localization(event);
        }
    }
}

void task_Battery(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_Battery, &event, portMAX_DELAY)) {
            handle_event_Battery(event);
        }
    }
}

void task_MissionControl(void *params) {
    char event[32];
    while (1) {
        if (xQueueReceive(queue_MissionControl, &event, portMAX_DELAY)) {
            handle_event_MissionControl(event);
        }
    }
}

int main() {
    queue_Navigation = xQueueCreate(10, sizeof(char[32]));
    queue_Camera = xQueueCreate(10, sizeof(char[32]));
    queue_Communication = xQueueCreate(10, sizeof(char[32]));
    queue_ObstacleAvoidance = xQueueCreate(10, sizeof(char[32]));
    queue_Localization = xQueueCreate(10, sizeof(char[32]));
    queue_Battery = xQueueCreate(10, sizeof(char[32]));
    queue_MissionControl = xQueueCreate(10, sizeof(char[32]));
    xTaskCreate(task_Navigation, "Navigation", 1000, NULL, 2, NULL);
    xTaskCreate(task_Camera, "Camera", 1000, NULL, 2, NULL);
    xTaskCreate(task_Communication, "Communication", 1000, NULL, 2, NULL);
    xTaskCreate(task_ObstacleAvoidance, "ObstacleAvoidance", 1000, NULL, 2, NULL);
    xTaskCreate(task_Localization, "Localization", 1000, NULL, 2, NULL);
    xTaskCreate(task_Battery, "Battery", 1000, NULL, 2, NULL);
    xTaskCreate(task_MissionControl, "MissionControl", 1000, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}
