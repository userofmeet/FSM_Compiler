#include <string.h>

typedef enum {
    ERROR,
    DISCONNECTED,
    CONNECTING,
    DEGRADED,
    CONNECTED,
} Communication_State;

Communication_State current_state_Communication = ERROR;

void handle_event_Communication(const char* event) {
    switch (current_state_Communication) {
        case ERROR:
            if (strcmp(event, "retry") == 0) current_state_Communication = DISCONNECTED;
            break;
        case DISCONNECTED:
            if (strcmp(event, "initiate") == 0) current_state_Communication = CONNECTING;
            if (strcmp(event, "fail") == 0) current_state_Communication = ERROR;
            break;
        case CONNECTING:
            if (strcmp(event, "fail") == 0) current_state_Communication = DISCONNECTED;
            if (strcmp(event, "success") == 0) current_state_Communication = CONNECTED;
            break;
        case DEGRADED:
            if (strcmp(event, "recover") == 0) current_state_Communication = CONNECTED;
            if (strcmp(event, "lost_connection") == 0) current_state_Communication = CONNECTING;
            break;
        case CONNECTED:
            if (strcmp(event, "degrade") == 0) current_state_Communication = DEGRADED;
            if (strcmp(event, "lost_connection") == 0) current_state_Communication = CONNECTING;
            break;
    }
}
