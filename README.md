# Mqtt-BLE

An ESP32-arduino file for using the ESP32 as a listener for bluetooth devices.
Set your device MAC-addresses in the code, and your topic/payload for the mqtt, 
and the ESP32 will send MQTT-messages as long as it sees the given devices.

If you need more devices just add more addresses, and if you need more people,
just copy/paste the if-statements in the loop()-function at the bottom of the code.
