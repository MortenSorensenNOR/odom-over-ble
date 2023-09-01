#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

// Acceleromter values
float Ax, Ay, Az;
float Gx, Gy, Gz;

unsigned long ul_time;
unsigned long ul_last_time;
float f_time_diff;

// BLE Odom Service
BLEService OdomService("19B10000-E8F2-537E-4F6C-D104768A1214"); 
// BLE Odom Characteristic - custom 128-bit UUID, read and writable by central
BLECharacteristic OdomCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify | BLEWrite, 64, true);
void setup() {
    Serial.begin(9600);
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy failed!");
    }
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    BLE.setLocalName("Odom device");
    BLE.setAdvertisedService(OdomService);
    OdomService.addCharacteristic(OdomCharacteristic);
    BLE.addService(OdomService);   
    BLE.advertise();
    Serial.println("BLE Odom Peripheral, waiting for connections....");
}

void loop() {
    // Listen for BLE peripherals to connect: 
    BLEDevice central = BLE.central();

    // If a central is connected to peripheral:
    if (central) {
        Serial.print("Connected to central: ");
        // Print the central's MAC address:
        Serial.println(central.address());
        // While the central is still connected to peripheral:
        ul_time = millis();
        ul_last_time = millis();
        Ax = 0.0; Ay = 0.0; Az = 0.0;
        Gx = 0.0; Gy = 0.0; Gz = 0.0;
        while (central.connected()) {
            if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
                // Read acceleration data from IMU: 
                IMU.readAcceleration(Ax, Ay, Az);
                // Read gyroscope data from IMU: 
                IMU.readGyroscope(Gx, Gy, Gz);

                ul_time = millis();
                f_time_diff = float(ul_time - ul_last_time);

                // TODO: Implement euler integration for getting approximate position data
                
                // Send odometry data over bluetooth connection
                // Data is sent in a configurable 64 length byte buffer
                String data = String(Ax) + ", " + String(Ax) + ", " + String(Ay) + ", " + String(Gx) + ", " + String(Gy) + ", " + String(Gz) + ", ";
                byte buffer[data.length() + 1];
                memset(buffer, 0xC0, sizeof(buffer));
                data.getBytes(buffer, data.length() + 1);

                OdomCharacteristic.writeValue(buffer, data.length() + 1);
            }
            delay(0);
        }
        // When the central disconnects, print it out:
        Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
    }
}
