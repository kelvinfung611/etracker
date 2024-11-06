# ESP32 BLE Counter

This project uses an ESP32 to count recycables from two IR sensors and advertise the counts via Bluetooth Low Energy (BLE). The ESP32 acts as a BLE server, allowing a mobile phone to connect and read the counts.

## Features

- Connects to two IR sensors to detect events.
- Uses BLE to advertise the count of recycables detected by each sensor.
- Provides real-time updates to connected devices.

## Components

- **ESP32**
- **Two IR Sensors**
- **Two LEDs**
- **Jumper Wires**
- **Breadboard (optional)**

## Setup

1. **Hardware Connections:**
   - Connect the first IR sensor to pin `4` and the second IR sensor to pin `2`.
   - Connect the first LED to pin `22` and the second LED to pin `23`.
   - Ensure all components share a common ground.

2. **Software:**
   - Install the Arduino IDE if you haven't already.
   - Install the ESP32 board in Arduino IDE. [Instructions here](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md).
   - Install necessary libraries: `BLEDevice.h`, `BLEUtils.h`, `BLEServer.h`.

3. **Upload the Code:**
   - Open the provided `.ino` file in Arduino IDE.
   - Select the correct ESP32 board and port.
   - Upload the code to your ESP32.

## Usage

1. Power on the ESP32.
2. Use a BLE-enabled mobile app (like nRF Connect) to scan for devices.
3. Connect to the device named "eTracker_esp32".
4. Read the characteristic to see the current counts for `can` and `bottle`.

## Code Explanation

- **BLE Initialization**: Sets up the ESP32 as a BLE server with a specific service and characteristic.
- **Loop Function**: Continuously reads the sensor values, updates counts, and notifies connected devices of any changes.
- **Callbacks**: Handles BLE connection and disconnection events.

## Troubleshooting

- Ensure the ESP32 is powered correctly and connected to the computer for uploading the code.
- Verify that the wiring matches the pin definitions in the code.
- Use a BLE app to ensure your device is advertising correctly.

## License

This project is open-source and available under the MIT License.
