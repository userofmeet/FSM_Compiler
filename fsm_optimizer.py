def optimize_systems(systems):
    optimized_systems = []

    for obj in systems:
        state_patterns = {}
        for state in obj["states"]:
            # only consider transitions from real states (not ANY_STATE)
            transitions = [
                (event, dest)
                for (src, event, dest) in obj["transitions"]
                if src == state and src != "ANY_STATE" and dest != "ANY_STATE"
            ]
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
        for (source, event, dest) in obj["transitions"]:
            # preserve special-case ANY_STATE transitions without optimization
            if source == "ANY_STATE" or dest == "ANY_STATE":
                new_transitions.append((source, event, dest))
                continue

            new_source = state_equivalents[source]
            new_dest = state_equivalents[dest]
            new_transitions.append((new_source, event, new_dest))

        new_transitions = list(set(new_transitions))  
        new_states = list(set(state_equivalents.values()) | {s for s in obj["states"] if s == "ANY_STATE"})

        optimized_systems.append({
            "name": obj["name"],
            "states": new_states,
            "events": obj["events"],
            "transitions": new_transitions
        })

        if len(new_states) < len(obj["states"]):
            print(f"[INFO] Optimized '{obj['name']}': {len(obj['states'])} → {len(new_states)} states")

    return optimized_systems
