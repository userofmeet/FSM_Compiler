# FSM Compiler for Embedded Systems 🚀

This project is a Python-based compiler that transforms user-defined **Finite State Machine (FSM)** descriptions into modular, production-ready **C code** tailored for **embedded systems** like **STM32**, **ESP32**, and **Arduino**, all running **FreeRTOS**.

---

## ✨ Features

- 🔁 Support for **multiple FSMs** in a single description file.
- ⚡ Auto-generation of `.c` files for each FSM.
- 🎯 Centralized `rtos_main.c` to manage all FSMs as FreeRTOS tasks.
- 📦 Modular code structure for scalability and maintainability.
- 🧠 Optimization: Detects and minimizes equivalent or redundant states.
- 🛠️ Plug-and-play design—write FSMs in plain text and generate working code instantly.

---

## 🧰 Technologies Used

- **Python** – for the FSM compiler and optimization engine.
- **Embedded C** – for the generated output code.
- **FreeRTOS** – for task scheduling and modular execution.
- **GCC / Keil / PlatformIO (VS Code)** – for compiling and deploying the generated code.

---

## 📁 Folder Structure
```
fsm-compiler/
│
├── input # input fsm files
│ └── drone_system.fsm
├── output/ # Auto-generated C files
│ ├── navigation.c
│ ├── camera.c
│ ├── rtos_main.c
│ └── ...
├── README.md
├── codegen_c.py # Generates C code for each FSM
├── fsm_optimizer.py # Optimizes FSMs (e.g. merges redundant states)
├── fsm_parser.py # Parses FSM input file
├── generate_rtos.py # Builds RTOS-compatible task manager (rtos_main.c)
├── main.py # Main compiler entry point
├── testing.c # Optional test driver in C
└── README.md
```


## ⚡ Features

- ✅ Converts multiple FSMs into individual `.c` files
- 🧠 FSM optimization: detects and removes equivalent states
- 🔀 Generates a central `rtos_main.c` to manage tasks via FreeRTOS
- 🛠️ Supports STM32, ESP32, Arduino (via PlatformIO, Keil, or GCC)
- 📄 Human-readable FSM definition format
- 🎯 Plug-and-play compiler (no GUI, simple CLI-based tool)

---

## 🚀 How to Use

1. **Prepare FSM input**:
   - Write your FSMs in the file `input/drone_system.fsm`.

2. **Run the compiler**:
   ```bash
   python main.py
   ```

3. **Find output C files in the output/ directory**
  - Each FSM becomes its own .c file.
  - rtos_main.c is created to handle task creation for each FSM.

4. **Compile using:**
  - PlatformIO (VS Code)
  - Keil
  - STM32CubeIDE
  - Arduino IDE (if compatible)
  - Any FreeRTOS-enabled toolchain

## 📚 Example FSMs Included

FSMs in the sample input:
  - Navigation
  - Camera
  - Communication
  - Localization
  - MissionControl
  - Battery
  - ObstacleAvoidance
These FSMs model different drone subsystems and demonstrate how complex behavior can be modularized.


## 🧪 Applications
  - Drones & UAVs
  - Robotics systems
  - Industrial automation
  - Embedded AI control loops
  - Event-driven IoT devices

## 📜 License
MIT License

## 🤝 Contribute
Pull requests and feedback are welcome! To suggest improvements or new features, open an issue.

## 📫 Contact
For questions, reach out via GitHub issues or fork and build on it!

## 👤 Author
**Meet Jain**
📧 [meetjain538@gmail.com]
🔗 github.com/userofmeet

```
“Automating what should’ve never been manual in the first place.”
```
