#include <string.h>

typedef enum {
    CRITICAL,
    SHUTDOWN,
    DISCHARGING,
    LOW,
    FULL,
    CHARGING,
} Battery_State;

Battery_State current_state_Battery = CRITICAL;

void handle_event_Battery(const char* event) {
    switch (current_state_Battery) {
        case CRITICAL:
            if (strcmp(event, "power_off") == 0) current_state_Battery = SHUTDOWN;
            if (strcmp(event, "plug_in") == 0) current_state_Battery = CHARGING;
            break;
        case SHUTDOWN:
            break;
        case DISCHARGING:
            if (strcmp(event, "plug_in") == 0) current_state_Battery = CHARGING;
            if (strcmp(event, "alert_low") == 0) current_state_Battery = LOW;
            break;
        case LOW:
            if (strcmp(event, "plug_in") == 0) current_state_Battery = CHARGING;
            if (strcmp(event, "alert_critical") == 0) current_state_Battery = CRITICAL;
            break;
        case FULL:
            if (strcmp(event, "unplug") == 0) current_state_Battery = DISCHARGING;
            break;
        case CHARGING:
            if (strcmp(event, "charge") == 0) current_state_Battery = FULL;
            break;
    }
}
