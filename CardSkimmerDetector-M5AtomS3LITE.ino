#include <BLEDevice.h>
#include <M5AtomS3.h>
#include <vector>
#include <regex>

const int scanTime = 5; // BLE scan duration in seconds
std::vector<String> detectedDevices; // Stores all detected devices
std::vector<String> detectedSkimmers; // Stores detected skimmers
const int maxDevicesStored = 50; // Limit for stored devices

// Known skimmer names
String knownSkimmerNames[] = {"HC-03", "HC-05", "HC-06", "HC-08", "RNBT"};

bool scanning = false; // Flag to indicate if scanning is in progress

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) override {
        String deviceInfo = "Name: " + String(advertisedDevice.getName().c_str()) +
                            ", Addr: " + String(advertisedDevice.getAddress().toString().c_str());
        
        // Regular expression to match "RNBT-xxxx" pattern
        std::regex rnbtPattern("RNBT-[A-Za-z0-9]{4}");
        std::string devName = advertisedDevice.getName();
        String deviceAddress = String(advertisedDevice.getAddress().toString().c_str());

        bool isRnSkimmer = deviceAddress.startsWith("00:06:66");
        
        // Check against the MAC address pattern for manufacturing date
        int year1 = (deviceAddress.charAt(0) - '0') * 10 + (deviceAddress.charAt(1) - '0');
        int year2 = (deviceAddress.charAt(3) - '0') * 10 + (deviceAddress.charAt(4) - '0');
        int month = (deviceAddress.charAt(6) - '0') * 10 + (deviceAddress.charAt(7) - '0');
        int day = (deviceAddress.charAt(9) - '0') * 10 + (deviceAddress.charAt(10) - '0');
        int year = year1 * 100 + year2;
        int currentYear = 2025; // Dynamically set this to the current year

        // Evaluate if the device is a known skimmer based on its name, RNBT pattern, MAC prefix, or manufacturing date
        bool isSkimmer = std::regex_search(devName, rnbtPattern) || isRnSkimmer;
        for (String skimmerName : knownSkimmerNames) {
            if (devName.find(skimmerName.c_str()) != std::string::npos) {
                isSkimmer = true;
                break;
            }
        }

        if ((year >= 2013 && year <= currentYear) && (month >= 1 && month <= 12) && (day >= 1 && day <= 31)) {
            isSkimmer = true;
        }

        if (isSkimmer) {
            detectedSkimmers.push_back(deviceInfo);
            Serial.println("Skimmer Detected: " + deviceInfo);
        } else if (detectedDevices.size() < maxDevicesStored) {
            detectedDevices.push_back(deviceInfo);
            Serial.println("Device Detected: " + deviceInfo);
        }
    }
};

void startBLEScan() {
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), false);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(scanTime, false);
  Serial.println("BLE scan complete");
}

void handleScan() {
  detectedDevices.clear();
  detectedSkimmers.clear();
  startBLEScan();
  Serial.println("Scanning...");
}

void handleClear() {
  detectedDevices.clear();
  detectedSkimmers.clear();
  Serial.println("Data cleared.");
}

void setup() {
  AtomS3.begin();
  Serial.begin(115200);
  // Start BLE scan on setup
  startBLEScan();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'a') {
      handleScan();
    } else if (c == 'b') {
      handleClear();
    }
  }
}
