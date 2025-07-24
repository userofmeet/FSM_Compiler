#include <string.h>

typedef enum {
    SNAPSHOT,
    OFF,
    STREAMING,
    CAM_IDLE,
    RECORDING,
} Camera_State;

Camera_State current_state_Camera = SNAPSHOT;

void handle_event_Camera(const char* event) {
    switch (current_state_Camera) {
        case SNAPSHOT:
            if (strcmp(event, "resume") == 0) current_state_Camera = RECORDING;
            break;
        case OFF:
            break;
        case STREAMING:
            if (strcmp(event, "stop") == 0) current_state_Camera = CAM_IDLE;
            break;
        case CAM_IDLE:
            if (strcmp(event, "start_stream") == 0) current_state_Camera = STREAMING;
            if (strcmp(event, "start_record") == 0) current_state_Camera = RECORDING;
            if (strcmp(event, "shutdown") == 0) current_state_Camera = OFF;
            if (strcmp(event, "take_photo") == 0) current_state_Camera = SNAPSHOT;
            break;
        case RECORDING:
            if (strcmp(event, "stop") == 0) current_state_Camera = CAM_IDLE;
            if (strcmp(event, "take_photo") == 0) current_state_Camera = SNAPSHOT;
            if (strcmp(event, "pause") == 0) current_state_Camera = SNAPSHOT;
            break;
    }
}
