#include <string.h>

typedef enum {
    COMPLETED,
    READY,
    PAUSED,
    PLANNING,
    ABORTED,
    IN_PROGRESS,
} MissionControl_State;

MissionControl_State current_state_MissionControl = COMPLETED;

void handle_event_MissionControl(const char* event) {
    switch (current_state_MissionControl) {
        case COMPLETED:
            break;
        case READY:
            if (strcmp(event, "start") == 0) current_state_MissionControl = IN_PROGRESS;
            break;
        case PAUSED:
            if (strcmp(event, "abort") == 0) current_state_MissionControl = ABORTED;
            if (strcmp(event, "resume") == 0) current_state_MissionControl = IN_PROGRESS;
            break;
        case PLANNING:
            if (strcmp(event, "plan_ready") == 0) current_state_MissionControl = READY;
            break;
        case ABORTED:
            if (strcmp(event, "plan_ready") == 0) current_state_MissionControl = PLANNING;
            break;
        case IN_PROGRESS:
            if (strcmp(event, "abort") == 0) current_state_MissionControl = ABORTED;
            if (strcmp(event, "pause") == 0) current_state_MissionControl = PAUSED;
            if (strcmp(event, "complete") == 0) current_state_MissionControl = COMPLETED;
            break;
    }
}
