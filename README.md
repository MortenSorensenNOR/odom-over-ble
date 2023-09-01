# odom-over-ble
Test project for sending odometry data over BLE-connection from an Arduino Nano RP2040 to host running rust.

Plan for sending odometry over bluetooth from Arduino nano RP2040 to host (Linux x86-64):

1. Write code to read sensordata, and use the data to get an approximate orientation and position of nano
2. Write code for publishing bluetooth Uuid, and sending position and orientationdata over the BLE-connection
3. Write js application for scanning available bluetooth entities, and connecting to the nano's spesific Uuid
4. Read data from BLE connection
5. Visualize data in 3D (probably using the THREE.js)

Helpful links: 
- https://docs.arduino.cc/tutorials/nano-rp2040-connect/rp2040-ble-device-to-device
- https://developer.chrome.com/articles/bluetooth/
