// Connect to Bluetooth and subscribe to odometry service
const button = document.getElementById("request_bluetooth");
button.addEventListener('pointerup', function(event) {
	navigator.bluetooth.requestDevice({ filters: [{ name: 'Odom device' }], optionalServices: ['19b10000-e8f2-537e-4f6c-d104768a1214'] })
	.then(device => device.gatt.connect())
	.then(server => server.getPrimaryService('19b10000-e8f2-537e-4f6c-d104768a1214'))
	.then(service => service.getCharacteristic('19b10001-e8f2-537e-4f6c-d104768a1214'))
	.then(characteristic => characteristic.startNotifications())
	.then(characteristic => {
		characteristic.addEventListener('characteristicvaluechanged', parseBluetoothOdometry)
	})
	.catch(error => { console.error(error); });
});

// Extract data from datastream
let Ax = 0, Ay = 0, Az = 0, Gx = 0, Gy = 0, Gz = 0;
const data_p = document.getElementById("data");
var enc = new TextDecoder('utf-8'); // always utf-8
function parseBluetoothOdometry(event) {
	const value = event.target.value;
	const value_string = enc.decode(value)
	const value_floats = value_string.split(', ');
	Ax = value_floats[0];
	Ay = value_floats[1];
	Az = value_floats[2];
	Gx = value_floats[3];
	Gy = value_floats[4];
	Gz = value_floats[5];
	data_p.innerHTML = `Acc: (${value_floats[0]}, ${value_floats[1]}, ${value_floats[2]}) Gyr: (${value_floats[3]}, ${value_floats[4]}, ${value_floats[5]})`;
}