import os
def create_c_files(systems, output_folder):
    os.makedirs(output_folder, exist_ok=True)

    for obj in systems:
        name = obj['name']
        c_file_path = os.path.join(output_folder, f"{name.lower()}.c")
        with open(c_file_path, 'w') as c_file:
            c_file.write("#include <string.h>\n\n")
            c_file.write(f"typedef enum {{\n")
            for state in obj["states"]:
                c_file.write(f"    {state},\n")
            c_file.write(f"}} {obj}_State;\n\n")
            c_file.write(f"{obj}_State current_state_{obj} = {obj['states'][0]};\n\n")
            c_file.write(f"void handle_event_{obj}(const char* event) {{\n")
            c_file.write(f"    switch (current_state_{obj}) {{\n")
            for state in obj["states"]:
                c_file.write(f"        case {state}:\n")
                for src, event_name, dest in obj["transitions"]:
                    if src == state:
                        c_file.write(f"            if (strcmp(event, \"{event_name}\") == 0) current_state_{obj} = {dest};\n")
                c_file.write("            break;\n")
            c_file.write("    }\n}\n")
