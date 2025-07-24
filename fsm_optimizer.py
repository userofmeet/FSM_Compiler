def optimize_drone_systems(drone_systems):
    optimized_systems = []
    
    for drone in drone_systems:
        state_patterns = {}
        for state in drone["states"]:
            transitions = [(event, dest) for (src, event, dest) in drone["transitions"] if src == state]
            state_patterns[state] = tuple(sorted(transitions))
        pattern_to_state = {}
        state_equivalents = {}
        for state, pattern in state_patterns.items():
            if pattern in pattern_to_state:
                state_equivalents[state] = pattern_to_state[pattern]
            else:
                pattern_to_state[pattern] = state
                state_equivalents[state] = state

        new_transitions = []
        for (source, event, dest) in drone["transitions"]:
            new_source = state_equivalents[source]
            new_dest = state_equivalents[dest]
            new_transitions.append((new_source, event, new_dest))

        new_transitions = list(set(new_transitions))  
        new_states = list(set(state_equivalents.values()))

        optimized_systems.append({
            "name": drone["name"],
            "states": new_states,
            "events": drone["events"],
            "transitions": new_transitions
        })

        if len(new_states) < len(drone["states"]):
            print(f"[INFO] Optimized '{drone['name']}': {len(drone['states'])} → {len(new_states)} states")

    return optimized_systems