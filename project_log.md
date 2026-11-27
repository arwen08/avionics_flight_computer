**RP2040 (Raspberry Pi Pico) Avionics Flight Computer** 
**Project Log**

## Entry - 2026-11-16 |Hardware Order, VS Code Toolchain & GitHub Setup
**Objectives:**
1. Configure the VS Code + PlatformIO C++ environment for the RP2040, and initialize version control on GitHub for 
`avionics_flight_computer`.
2. Acquire the required hardware components
  
**Actions Taken:**
* Created the `avionics_flight_computer` PlatformIO project (`rpipico`, Arduino framework) in VS Code on macOS, configured `platformio.ini` with the Earle Philhower core (`maxgerhardt/platform-raspberrypi`) and Adafruit MPU6050/BMP3XX libraries, and set `Wire.setSDA(4)` and `Wire.setSCL(5)` in `src/main.cpp`.
  
* Created the public `avionics_flight_computer` repository on GitHub without initializing a README, `.gitignore`, or license, and initialized Git, committed the baseline files, added the remote, and pushed to `main` from the VS Code terminal on macOS.
  
* Obtained necessary components for project: 
  * Raspberry Pi Pico with pre-soldered headers,
  * DFRobot Fermion MPU-6050 `SEN0142`, 
  * Adafruit BMP388 `ADA3966`, 
  * 3.3 V MicroSD breakout `106696`, 
  * SPDT ON-ON latching toggle switch, 
  * 50 cm Micro-USB data/power cable,
  * X GB MicroSD card,
  * Male-to-Male breadboard wires,
  * Female-to-Male breadboard wires,
  * Breadboard,
  * 10K Ohm and 220 Ohm resistors,
  * Micro Servo SG90,
  * and LEDs (various colours).

**Verification:** Confirmed clean PlatformIO compilation (`[SUCCESS]`) and verified the baseline repository files (`platformio.ini`, `src/main.cpp`, `.gitignore`) were pushed to the `main` branch on GitHub.

**Issues & Next Steps:** No issues. Next, complete soldering at iForge, verify switch continuity/current flow, wire the I2C0 bus (`GP4`/`GP5` on `3.3 V`), and run the I2C scanner to detect `0x68` and `0x77`.

## Entry — 2026-11-26 | iForge Soldering & SPDT Switch Continuity Check
**Objective:** Solder headers onto the sensor/MicroSD boards, wire leads to the SPDT toggle switch, and verify switch continuity/current flow before I2C0 bring-up.

**Actions Taken:** Soldered headers on the MPU-6050, BMP388, and MicroSD breakout at iForge Mainspace, and soldered two leads onto the SPDT toggle switch (black on center COM lug, red on an outer lug) and secured with electrical tape.

**Verification:** Switch cleanly opens and closes the circuit when toggled without cutting out when leads are gently wiggled, see Fig. 1.1 & 1.2 in media and below. Tested switch with simple breadboard circuit that turned an LED on and off. 

**Figure 1.1:**
![Figure 1.1](media/figure_1.1.jpg)
**Figure 1.2:**
![Figure 1.2](media/figure_1.2.jpg)

**Issues & Next Steps:** The solder had a really hard time sticking to the wire and the switch lugs so it took a few attempts. Next time, wire the I2C0 bus (GP4 SDA, GP5 SCL on 3.3 V) and run the I2C scanner to confirm addresses 0x68 and 0x77.

## Entry — 2026-11-27 | I2C0 Bus Scan & Milestone 1 Verification
- **Objective:** Wire the MPU-6050 and BMP388 to the I2C0 bus on the 3.3 V rail of the breadboard, flash the I2C scanner in `src/main.cpp`, and verify hardware acknowledgement (`[ACK]`) on both sensor addresses.

- **Actions Taken:**
  - Wired the Raspberry Pi Pico, DFRobot Fermion MPU-6050 (`SEN0142`), and Adafruit BMP388 (`ADA3966`) on the breadboard using `GP4` (SDA) and `GP5` (SCL) on the 3.3 V rail.
  - Implemented and uploaded the 400 kHz I2C0 bus scanner in `src/main.cpp` using `Wire.setSDA(4)`, `Wire.setSCL(5)`, `Wire.begin()`, and `Wire.setClock(400000)` with a bounded startup wait for USB `Serial` at `115200` baud, sweeping 7-bit addresses `0x01`–`0x7E`, and removed a stray unguarded print line before the `devicesFound == 0` check.

- **Verification:** Confirmed across repeated scans in the PlatformIO Serial Monitor (`/dev/cu.usbmodem1101` at `115200` baud) that both `0x68` (MPU-6050) and `0x77` (BMP388) return `[ACK]` (`Total ACK devices: 2`) at 400 kHz with no `[ERR]` bus faults[cite: 2, 3].

- **Issues & Next Steps:** No hardware bus faults observed. Next: commit the updated `src/main.cpp` and scan output to `avionics_flight_computer`, then start Milestone 2 (initializing `Adafruit_MPU6050` and `Adafruit_BMP3XX`, measuring the resting gravity vector and gyroscope zero-rate bias at startup, and streaming raw sensor data over serial)[cite: 2, 3].

## New Entry 

