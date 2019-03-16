# Mqtt-BLE

An ESP32-arduino file for using the ESP32 as a listener for bluetooth devices.
Set your device MAC-addresses in the code, and your topic/payload for the mqtt, 
and the ESP32 will send MQTT-messages as long as it sees the given devices.

If you need more devices just add more addresses, and if you need more people,
just copy/paste the if-statements in the loop()-function at the bottom of the code.

# To transfer this code to your ESP32:

Go to File -> Preferences -> Additional Boards Manager URLs and add the following link:
https://dl.espressif.com/dl/package_esp32_index.json

Go to Tools -> Board -> Boards Manager and search for ESP32. Choose install.

When the Install is finished restart Arduino and select
Tools -> Board -> ESP32 Dev

Change Partition Scheme to No OTA(Large App)

Verify and Upload the code and you should be good to go.

The code will output debug-messages to Serial 115200, so it's probably a good idea to monitor this the first time you run it.

set the Arduino 
