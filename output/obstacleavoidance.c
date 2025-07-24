#include <string.h>

typedef enum {
    PATH_RECOVERED,
    STUCK,
    EVADING,
    CLEAR_PATH,
    OBSTACLE_DETECTED,
    OVERRIDE,
} ObstacleAvoidance_State;

ObstacleAvoidance_State current_state_ObstacleAvoidance = PATH_RECOVERED;

void handle_event_ObstacleAvoidance(const char* event) {
    switch (current_state_ObstacleAvoidance) {
        case PATH_RECOVERED:
            if (strcmp(event, "recover") == 0) current_state_ObstacleAvoidance = CLEAR_PATH;
            if (strcmp(event, "detect") == 0) current_state_ObstacleAvoidance = OBSTACLE_DETECTED;
            break;
        case STUCK:
            if (strcmp(event, "override") == 0) current_state_ObstacleAvoidance = OVERRIDE;
            break;
        case EVADING:
            if (strcmp(event, "recover") == 0) current_state_ObstacleAvoidance = PATH_RECOVERED;
            if (strcmp(event, "stuck") == 0) current_state_ObstacleAvoidance = STUCK;
            break;
        case CLEAR_PATH:
            if (strcmp(event, "detect") == 0) current_state_ObstacleAvoidance = OBSTACLE_DETECTED;
            break;
        case OBSTACLE_DETECTED:
            if (strcmp(event, "evade") == 0) current_state_ObstacleAvoidance = EVADING;
            break;
        case OVERRIDE:
            if (strcmp(event, "manual_clear") == 0) current_state_ObstacleAvoidance = PATH_RECOVERED;
            break;
    }
}
