#include <string.h>

typedef enum {
    PROCESSING,
    IDLE,
    ALERT,
    WAITING_INPUT,
    DISPLAYING_FEEDBACK,
} {'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]}_State;

{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]}_State current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]} = PROCESSING;

void handle_event_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]}(const char* event) {
    switch (current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]}) {
        case PROCESSING:
            if (strcmp(event, "feedback") == 0) current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]} = DISPLAYING_FEEDBACK;
            break;
        case IDLE:
            if (strcmp(event, "receive_input") == 0) current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]} = WAITING_INPUT;
            break;
        case ALERT:
            break;
        case WAITING_INPUT:
            if (strcmp(event, "process") == 0) current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]} = PROCESSING;
            break;
        case DISPLAYING_FEEDBACK:
            if (strcmp(event, "timeout") == 0) current_state_{'name': 'UserInterface', 'states': ['PROCESSING', 'IDLE', 'ALERT', 'WAITING_INPUT', 'DISPLAYING_FEEDBACK'], 'events': ['receive_input', 'process', 'feedback', 'alert_user', 'timeout', 'power_off'], 'transitions': [('PROCESSING', 'feedback', 'DISPLAYING_FEEDBACK'), ('ANY_STATE', 'power_off', 'SHUTDOWN'), ('WAITING_INPUT', 'process', 'PROCESSING'), ('IDLE', 'receive_input', 'WAITING_INPUT'), ('ANY_STATE', 'alert_user', 'ALERT'), ('DISPLAYING_FEEDBACK', 'timeout', 'IDLE')]} = IDLE;
            break;
    }
}
