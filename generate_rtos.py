import os

def create_rtos_main(systems, output_file):
    with open(output_file, 'w') as main_file:
        main_file.write('#include "FreeRTOS.h"\n')
        main_file.write('#include "task.h"\n')
        main_file.write('#include "queue.h"\n')
        main_file.write('#include <stdio.h>\n')
        main_file.write('#include <string.h>\n\n')

        # FSM enums + state variables
        for obj in systems:
            name = obj["name"]
            main_file.write(f"typedef enum {{\n")
            for state in obj["states"]:
                main_file.write(f"    {name.upper()}_{state},\n")
            main_file.write(f"}} {name}_State;\n\n")
            main_file.write(f"{name}_State current_state_{name} = {name.upper()}_{obj['states'][0]};\n\n")

        # Task definitions with FSM transitions
        for obj in systems:
            name = obj["name"]
            main_file.write(f"void task_{name}(void *params) {{\n")
            main_file.write("    char event[32];\n")
            main_file.write(f"    while (1) {{\n")
            main_file.write(f"        if (xQueueReceive(queue_{name}, &event, portMAX_DELAY)) {{\n")
            main_file.write(f"            switch (current_state_{name}) {{\n")
            for state in obj["states"]:
                main_file.write(f"                case {name.upper()}_{state}:\n")
                for src, event_name, dest in obj["transitions"]:
                    if src == state:
                        main_file.write(f"                    if (strcmp(event, \"{event_name}\") == 0) current_state_{name} = {name.upper()}_{dest};\n")
                main_file.write("                    break;\n")
            main_file.write("            }\n")
            main_file.write("        }\n")
            main_file.write("    }\n")
            main_file.write("}\n\n")

        # Queues
        for obj in systems:
            main_file.write(f"QueueHandle_t queue_{obj['name']};\n")
        main_file.write("\n")

        # Main function
        main_file.write("int main() {\n")
        for obj in systems:
            main_file.write(f"    queue_{obj['name']} = xQueueCreate(10, sizeof(char[32]));\n")
        for obj in systems:
            main_file.write(f'    xTaskCreate(task_{obj["name"]}, "{obj["name"]}", 1000, NULL, 2, NULL);\n')
        main_file.write("    vTaskStartScheduler();\n")
        main_file.write("    return 0;\n")
        main_file.write("}\n")
