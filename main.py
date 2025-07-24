from fsm_parser import parse_fsm_file
from fsm_optimizer import optimize_systems
from codegen_c import create_c_files
from generate_rtos import create_rtos_main
import os

input_file = "input/ground_robot.fsm"
output_folder = "output"
rtos_main_file = os.path.join(output_folder, "rtos_main.c")

# parse fsm defitions 
systems = parse_fsm_file(input_file)
# state reduction
systems = optimize_systems(systems)
# generate c files 
create_c_files(systems, output_folder)
# make the rtos file 
create_rtos_main(systems, rtos_main_file)

print("rtos code done")
