#include <string.h>

typedef enum {
    CONNECTING,
    LOST_SIGNAL,
    OFFLINE,
    CONNECTED,
    RECONNECTING,
} {'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]}_State;

{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]}_State current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = CONNECTING;

void handle_event_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]}(const char* event) {
    switch (current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]}) {
        case CONNECTING:
            if (strcmp(event, "establish_link") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = CONNECTED;
            break;
        case LOST_SIGNAL:
            if (strcmp(event, "attempt_reconnect") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = RECONNECTING;
            break;
        case OFFLINE:
            if (strcmp(event, "power_on") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = CONNECTING;
            break;
        case CONNECTED:
            if (strcmp(event, "lose_link") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = LOST_SIGNAL;
            break;
        case RECONNECTING:
            if (strcmp(event, "link_restored") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = CONNECTED;
            if (strcmp(event, "lose_link") == 0) current_state_{'name': 'Connectivity', 'states': ['CONNECTING', 'LOST_SIGNAL', 'OFFLINE', 'CONNECTED', 'RECONNECTING'], 'events': ['power_on', 'establish_link', 'lose_link', 'attempt_reconnect', 'link_restored'], 'transitions': [('CONNECTING', 'establish_link', 'CONNECTED'), ('LOST_SIGNAL', 'attempt_reconnect', 'RECONNECTING'), ('CONNECTED', 'lose_link', 'LOST_SIGNAL'), ('RECONNECTING', 'link_restored', 'CONNECTED'), ('RECONNECTING', 'lose_link', 'OFFLINE'), ('OFFLINE', 'power_on', 'CONNECTING')]} = OFFLINE;
            break;
    }
}
