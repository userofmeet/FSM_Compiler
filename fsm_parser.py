# format with fsm: states: events: and transitions: sections
def parse_fsm_file(file_path):
    drone_systems = []
    current_drone = {}
    parsing_mode = None

    with open(file_path, 'r') as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):  # skip empty files
            continue
        if line.startswith("fsm:"):
            if current_drone:  # save previous fsms
                drone_systems.append(current_drone)
            current_drone = {
                "name": line.replace("fsm:", "").strip(),
                "states": [],
                "events": [],
                "transitions": []
            }
            parsing_mode = None
        elif line.startswith("states:"):
            current_drone["states"] = [state.strip() for state in line.replace("states:", "").split(",")]
        elif line.startswith("events:"):
            current_drone["events"] = [event.strip() for event in line.replace("events:", "").split(",")]
        elif line.startswith("transitions:"):
            parsing_mode = "transitions"
        elif parsing_mode == "transitions":
            parts = line.split(":")
            transition = parts[0].strip()
            event = parts[1].strip()
            source, destination = [state.strip() for state in transition.split("->")]
            current_drone["transitions"].append((source, event, destination))

    if current_drone:  # last fms
        drone_systems.append(current_drone)

    return drone_systems