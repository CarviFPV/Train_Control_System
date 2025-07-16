# Train Control System

A remote-controlled G-scale locomotive system powered by NodeMCU ESP8266 microcontrollers. This project enables wireless control of model trains through a custom-built remote controller with rotary encoder input.

## 📋 Project Overview

This system consists of two main components:

- **TMF2-2 G-Scale Locomotive**: A 3D-printed train with integrated motor control and WiFi connectivity
- **Remote Controller**: A handheld device with rotary encoder for speed control and direction switching

## ✨ Features

- **Wireless Control**: WiFi-based communication between remote and locomotive
- **Variable Speed Control**: Smooth PWM-based speed regulation (-100 to +100)
- **Direction Control**: Forward/reverse operation with LED indicators
- **Web Interface**: Browser-based control panel for additional functionality
- **Real-time Feedback**: System status and diagnostics display
- **LED Status Indicators**: Visual feedback for WiFi connection and direction

## 🔧 Hardware Components

### Locomotive Components:

- NodeMCU ESP8266 microcontroller
- L9110S H-bridge motor driver
- 2x DC motors
- White and red LEDs
- Battery holder
- 3D-printed locomotive body

### Remote Controller Components:

- NodeMCU ESP8266 microcontroller
- Rotary encoder (with push button)
- WiFi status LED
- Direction indicator LEDs
- 3D-printed controller housing

## 📦 3D Printable Parts

### Locomotive:

- **Main Body**: [TMF2-2 RhB Scale G Locomotive](https://makerworld.com/en/models/1609405-tmf2-2-rhb-scale-g-locomotive#profileId-1697519)

### Remote Controller:

- **Controller Housing**: [Remote Control for G-Scale Locomotive](https://makerworld.com/en/models/1609494-remote-control-for-the-g-scale-locomotive#profileId-1697623)

### Track System:

- **Curves**: [G-Scale Train Tracks](https://makerworld.com/en/models/1608501-g-scale-train-tracks#profileId-1696464)
- **Straight Tracks**: [Straight G-Scale Train Tracks](https://makerworld.com/en/models/1608589-straight-g-scale-train-tracks#profileId-1696575)
- **Left Switch**: [Left Switch Track Scale G](https://makerworld.com/en/models/1608801-left-switch-track-scale-g#profileId-1696815)
- **Right Switch**: [Right Switch Track Scale G](https://makerworld.com/en/models/1608777-right-switch-track-scale-g#profileId-1696788)

## 🔌 Wiring Diagrams

### Locomotive Wiring (train_system.ino):

```
NodeMCU -> L9110S Motor Driver
D1 -> Motor1A (Motor 1 Input A)
D2 -> Motor1B (Motor 1 Input B)
D4 -> Motor2A (Motor 2 Input A)
D3 -> Motor2B (Motor 2 Input B)

NodeMCU -> LEDs
D5 -> White LED (Forward indicator)
D6 -> Red LED (Reverse indicator)
```

### Remote Controller Wiring (Train_controller.ino):

```
NodeMCU -> Rotary Encoder
D6 -> CLK (Clock)
D5 -> DT (Data)
D7 -> SW (Switch/Button)

NodeMCU -> LEDs
D0 -> WiFi Status LED
D1 -> Forward Direction LED
D2 -> Reverse Direction LED
```

## 🚀 Setup Instructions

### 1. Prepare NodeMCU Boards

1. Flash NodeMCU firmware to both ESP8266 boards
   - Follow: [How to Flash NodeMCU Firmware](https://www.instructables.com/How-to-Flash-NodeMCU-Firmware-in-ESP8266/)
2. Install Arduino IDE and ESP8266 board support
   - Guide: [NodeMCU ESP8266 Setup Guide](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)

### 2. Upload Code

1. **Locomotive**: Upload `train_system/train_system.ino` to the locomotive's NodeMCU
2. **Remote Controller**: Upload `Train_controller/Train_controller.ino` to the remote's NodeMCU

### 3. Assembly Instructions

#### Locomotive Assembly:

1. Install motors in the base plate as shown in build photos
2. Connect L9110S motor driver according to wiring diagram
3. Wire LEDs for direction indication
4. Install battery holder underneath the locomotive
5. Mount NodeMCU in designated compartment
6. Install on/off switch in cockpit area
7. Assemble remaining 3D-printed parts

#### Remote Controller Assembly:

1. Print all remote controller parts
2. Install rotary encoder in housing
3. Connect LEDs for status indication
4. Wire according to provided diagram
5. Assemble housing components

## 📡 Operation

### WiFi Connection:

- **SSID**: `TrainAP`
- **Password**: `12345678`
- **Web Interface**: http://192.168.4.1

### Remote Control:

- **Rotate Encoder**: Adjust speed (-100 to +100)
- **Press Button**: Toggle direction (Forward/Reverse)
- **WiFi LED**: Indicates connection status
- **Direction LEDs**: Show current movement direction

### Web Interface Features:

- Speed control slider
- PWM input field
- System diagnostics (MAC, IP, RSSI, CPU frequency, memory usage)

## 📋 System Information

The web interface displays real-time system information:

- MAC Address
- Local IP Address
- WiFi Signal Strength (RSSI)
- CPU Frequency
- Flash Memory Size
- Free Heap Memory
- Flash Chip ID

## 🔧 Technical Specifications

- **Control Range**: Variable speed from -100 to +100
- **Communication**: WiFi (ESP8266 Access Point)
- **Motor Control**: PWM-based L9110S H-bridge
- **Power**: Battery-operated (voltage depends on motor requirements)
- **Scale**: G-Scale (1:22.5)

## 📁 File Structure

```
Train_Control_System/
├── train_system/
│   └── train_system.ino          # Locomotive control code
├── Train_controller/
│   └── Train_controller.ino      # Remote controller code
└── README.md                     # This documentation
```

## 🤝 Contributing

Feel free to contribute improvements, bug fixes, or additional features. Please ensure all changes are well-documented and tested.

## 📜 License

This project is open-source. Please check individual component licenses for 3D models and external libraries.

## 🔗 Additional Resources

- [NodeMCU Documentation](https://nodemcu.readthedocs.io/)
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [L9110S Motor Driver Datasheet](https://www.elecrow.com/download/datasheet-l9110.pdf)

---

**Note**: Ensure proper safety precautions when working with electronics and power supplies. Always disconnect power when making wiring changes.
