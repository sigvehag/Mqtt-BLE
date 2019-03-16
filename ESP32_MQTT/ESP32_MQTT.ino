#include "WiFi.h"
#include <PubSubClient.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// WIFI
const char* ssid = "YOUR_SSID";
const char* password  = "YOUR_WIFI_PASSWORD";
WiFiClient espClient;

// MQTT
const char* mqtt_server = "MQTT_SERVER_IP";
int port = 1883; //YOUR PORT - Standard for MQTT is 1883
const char* topic = "BLEStatus"; // YOUR TOPIC
const char* person1payload = "Jack/state"; // Set your payloads here
const char* person2payload = "Jill/state";
PubSubClient client(espClient);

//Bluetooth
int BTScanTime = 5;
BLEScan* pBLEScan;
BLEAddress tag1 = BLEAddress("ff:ff:ff:ff:ff:ff"); //Your address here
BLEAddress tag2 = BLEAddress("ff:ff:ff:ff:ff:ff"); //Your address here

BLEAddress phone1 = BLEAddress("ff:ff:ff:ff:ff:ff"); //Your address here
BLEAddress phone2 = BLEAddress("ff:ff:ff:ff:ff:ff"); //Your address here

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  // For Serial Debugging
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup(){
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, port); 
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void setup_wifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("BLEPresence")) {
      Serial.println("connected");
      client.publish(topic,"BLETracker Conected"); //This should appear if you sub to your topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  BLEScanResults foundDevices = pBLEScan->start(BTScanTime, false);
  for (int i = 0; i < foundDevices.getCount(); i++){
    BLEAddress found = foundDevices.getDevice(i).getAddress();
    if (found.equals(tag1) || found.equals(phone1)){
      client.publish(topic, person1payload);
    }
    if (found.equals(tag2) || found.equals(phone2)){
      client.publish(topic, person2payload);
    }
  }
  
  client.loop();
  pBLEScan->clearResults();
  delay(5000); // Scan every 5 seconds
}

