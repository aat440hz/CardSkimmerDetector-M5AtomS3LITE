# Card Skimmer Detector for M5AtomS3 Lite

This project provides a BLE scanner designed to detect and identify potential card skimmers in public spaces. Originally developed for the M5StickC Plus, it has now been optimized for the M5AtomS3 Lite, offering enhanced performance and portability. Using BLE technology, it scans for known skimmer signatures and alerts users to potential threats. 

## Features

- BLE scanning for detecting devices with known skimmer signatures (e.g., specific device names, MAC address patterns).
- Uses the M5AtomS3 Lite for improved performance and portability.
- Serial output for detected devices, allowing for easy monitoring.
- Supports commands via Serial for starting scans and clearing detected device lists.

## Setup

1. **Hardware Required**: M5AtomS3 Lite device.
2. **Software Requirements**:
   - Arduino IDE
   - M5Atom library
   - BLEDevice library

### Installation

1. Install the Arduino IDE and add the M5Atom board to your Arduino IDE.
2. Install the required libraries (`BLEDevice`, `M5Atom`) through the Arduino Library Manager.
3. Load the provided sketch onto your M5AtomS3 Lite device.

## Usage

1. Power on the M5AtomS3 Lite device.
2. Connect the M5AtomS3 Lite to your computer or to an Android device using a USB cable.
3. Open the Serial USB Terminal app by Kai Morich on your Android phone, or use the Arduino IDE's Serial Monitor.
4. Send the command 'a' to start a BLE scan for devices. Detected devices and any potential skimmers will be output to the Serial console.
5. Send the command 'b' to clear the list of detected devices and skimmers.
6. Repeat the scan as needed when visiting new locations or to check for new devices.

### Using with Serial USB Terminal App

1. Connect your Android device to the M5AtomS3 Lite via USB-C to USB-C cable.
2. Open the Serial USB Terminal app and select the correct USB device and baud rate (115200).
3. Use the app's console to send commands ('a' to scan, 'b' to clear) and view detected devices.

## Credits

- Special thanks to Kai Morich for the Serial USB Terminal app, facilitating mobile connectivity and control.
