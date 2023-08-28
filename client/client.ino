#include <ArduinoBLE.h>

BLEService LEDService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic LEDCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify | BLEWrite);
void setup() {
  Serial.begin(9600);
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
  }
  BLE.setLocalName("Button Device");
  BLE.setAdvertisedService(LEDService);
  LEDService.addCharacteristic(LEDCharacteristic);
  BLE.addService(LEDService);   
  BLE.advertise();
  Serial.println("BLE LED Peripheral, waiting for connections....");
}

void loop() {
  // listen for BLE peripherals to connect: 
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // while the central is still connected to peripheral:
    while (central.connected()) {

    }
    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
