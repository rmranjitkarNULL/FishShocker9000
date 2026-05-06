# FishShocker9000
A hardware/software system for high-voltage pulse generation and control, integrating custom PCB design, embedded firmware, and testing tools.

---

## Overview
FishShocker9000 was developed as a project to explore **embedded systems design, PCB layout, and high-voltage electronics**.  
The system combines custom hardware with **C/C++ firmware** to generate controlled electrical pulses, managed through a modular and extensible software stack.

---

## Hardware
- **Custom PCB Design** (schematics + board layouts)  
- Power delivery circuits for safe and reliable pulse generation  
- Signal conditioning and protection hardware  
- Mixed-signal layout considerations for high-voltage operation  

---

## Software
- Developed in **C/C++** using [PlatformIO](https://platformio.org/)  
- Modular code structure:
  - `include/` → headers  
  - `src/` → main firmware logic  
  - `lib/` → supporting libraries  
  - `test/` → test scripts and validation routines  
- Python scripts for testing and automation  
- Real-time control of timing and pulse delivery  

---

## Features
- Precise pulse generation and control  
- Configurable timing and waveform parameters  
- Modular design for hardware/firmware scalability  
- PCB + firmware tightly integrated for performance and safety  

---

## Repository Structure
FishShocker9000/
├── include/ # Header files
├── lib/ # Custom libraries
├── src/ # Firmware source code
├── test/ # Testing and validation scripts
├── pcb/ # PCB design files (schematics, layouts)
└── README.md # Project documentation

---

## Future Improvements
- Add microcontroller-based UI for parameter tuning  
- Improve PCB design for efficiency and miniaturization  
- Expand safety features and protection circuitry  
- Extend testing framework for automated validation  
