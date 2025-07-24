import os
def create_c_files(drone_systems, output_folder):
    os.makedirs(output_folder, exist_ok=True)

    for drone in drone_systems:
        drone_name = drone['name']
        c_file_path = os.path.join(output_folder, f"{drone_name.lower()}.c")
        with open(c_file_path, 'w') as c_file:
            c_file.write("#include <string.h>\n\n")
            c_file.write(f"typedef enum {{\n")
            for state in drone["states"]:
                c_file.write(f"    {state},\n")
            c_file.write(f"}} {drone_name}_State;\n\n")
            c_file.write(f"{drone_name}_State current_state_{drone_name} = {drone['states'][0]};\n\n")
            c_file.write(f"void handle_event_{drone_name}(const char* event) {{\n")
            c_file.write(f"    switch (current_state_{drone_name}) {{\n")
            for state in drone["states"]:
                c_file.write(f"        case {state}:\n")
                for src, event_name, dest in drone["transitions"]:
                    if src == state:
                        c_file.write(f"            if (strcmp(event, \"{event_name}\") == 0) current_state_{drone_name} = {dest};\n")
                c_file.write("            break;\n")
            c_file.write("    }\n}\n")