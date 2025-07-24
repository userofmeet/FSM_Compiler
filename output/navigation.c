#include <string.h>

typedef enum {
    DESCENDING,
    CRUISE,
    HOLDING,
    IDLE,
    LANDING,
    ASCENDING,
    TAKEOFF,
} Navigation_State;

Navigation_State current_state_Navigation = DESCENDING;

void handle_event_Navigation(const char* event) {
    switch (current_state_Navigation) {
        case DESCENDING:
            if (strcmp(event, "begin_landing") == 0) current_state_Navigation = LANDING;
            break;
        case CRUISE:
            if (strcmp(event, "hold_position") == 0) current_state_Navigation = HOLDING;
            if (strcmp(event, "begin_descent") == 0) current_state_Navigation = DESCENDING;
            if (strcmp(event, "emergency") == 0) current_state_Navigation = DESCENDING;
            break;
        case HOLDING:
            if (strcmp(event, "resume_cruise") == 0) current_state_Navigation = CRUISE;
            break;
        case IDLE:
            if (strcmp(event, "start_mission") == 0) current_state_Navigation = TAKEOFF;
            break;
        case LANDING:
            if (strcmp(event, "landed") == 0) current_state_Navigation = IDLE;
            break;
        case ASCENDING:
            if (strcmp(event, "reach_altitude") == 0) current_state_Navigation = CRUISE;
            break;
        case TAKEOFF:
            if (strcmp(event, "reach_altitude") == 0) current_state_Navigation = ASCENDING;
            break;
    }
}
