#include <string.h>

typedef enum {
    RUNNING_CHECKS,
    IDLE,
    ERROR_DETECTED,
    REPORTING,
    MAINTENANCE,
} {'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]}_State;

{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]}_State current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = RUNNING_CHECKS;

void handle_event_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]}(const char* event) {
    switch (current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]}) {
        case RUNNING_CHECKS:
            if (strcmp(event, "detect_error") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = ERROR_DETECTED;
            if (strcmp(event, "resolve") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = IDLE;
            break;
        case IDLE:
            if (strcmp(event, "initiate_check") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = RUNNING_CHECKS;
            break;
        case ERROR_DETECTED:
            if (strcmp(event, "report") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = REPORTING;
            break;
        case REPORTING:
            if (strcmp(event, "schedule_maintenance") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = MAINTENANCE;
            break;
        case MAINTENANCE:
            if (strcmp(event, "resolve") == 0) current_state_{'name': 'Diagnostics', 'states': ['RUNNING_CHECKS', 'IDLE', 'ERROR_DETECTED', 'REPORTING', 'MAINTENANCE'], 'events': ['initiate_check', 'detect_error', 'report', 'resolve', 'schedule_maintenance'], 'transitions': [('ERROR_DETECTED', 'report', 'REPORTING'), ('RUNNING_CHECKS', 'detect_error', 'ERROR_DETECTED'), ('MAINTENANCE', 'resolve', 'IDLE'), ('IDLE', 'initiate_check', 'RUNNING_CHECKS'), ('RUNNING_CHECKS', 'resolve', 'IDLE'), ('REPORTING', 'schedule_maintenance', 'MAINTENANCE')]} = IDLE;
            break;
    }
}
