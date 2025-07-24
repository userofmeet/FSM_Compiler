def create_rtos_main(drone_systems, output_file):
    with open(output_file, 'w') as main_file:
        main_file.write('#include "FreeRTOS.h"\n')
        main_file.write('#include "task.h"\n')
        main_file.write('#include "queue.h"\n')
        main_file.write('#include <stdio.h>\n')
        main_file.write('#include <string.h>\n\n')

        for drone in drone_systems:
            main_file.write(f'extern void handle_event_{drone["name"]}(const char*);\n')
        main_file.write("\n")

        for drone in drone_systems:
            main_file.write(f'QueueHandle_t queue_{drone["name"]};\n')

        for drone in drone_systems:
            main_file.write(f"""
void task_{drone['name']}(void *params) {{
    char event[32];
    while (1) {{
        if (xQueueReceive(queue_{drone['name']}, &event, portMAX_DELAY)) {{
            handle_event_{drone['name']}(event);
        }}
    }}
}}\n""")

        main_file.write("\nint main() {\n")
        for drone in drone_systems:
            main_file.write(f'    queue_{drone["name"]} = xQueueCreate(10, sizeof(char[32]));\n')
        for drone in drone_systems:
            main_file.write(f'    xTaskCreate(task_{drone["name"]}, "{drone["name"]}", 1000, NULL, 2, NULL);\n')
        main_file.write('    vTaskStartScheduler();\n    return 0;\n}\n')