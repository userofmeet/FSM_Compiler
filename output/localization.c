#include <string.h>

typedef enum {
    REACQUIRING,
    LOCKED,
    SEARCHING,
    UNAVAILABLE,
    LOST_FIX,
} Localization_State;

Localization_State current_state_Localization = REACQUIRING;

void handle_event_Localization(const char* event) {
    switch (current_state_Localization) {
        case REACQUIRING:
            if (strcmp(event, "gps_fix") == 0) current_state_Localization = LOCKED;
            if (strcmp(event, "lose_fix") == 0) current_state_Localization = LOST_FIX;
            break;
        case LOCKED:
            if (strcmp(event, "drift_detected") == 0) current_state_Localization = SEARCHING;
            if (strcmp(event, "lose_fix") == 0) current_state_Localization = LOST_FIX;
            break;
        case SEARCHING:
            if (strcmp(event, "gps_fix") == 0) current_state_Localization = LOCKED;
            break;
        case UNAVAILABLE:
            if (strcmp(event, "start_search") == 0) current_state_Localization = SEARCHING;
            break;
        case LOST_FIX:
            if (strcmp(event, "reacquire") == 0) current_state_Localization = REACQUIRING;
            break;
    }
}
