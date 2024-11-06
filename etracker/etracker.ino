#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <Wire.h>

// Randomly generated UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Defining pins
#define led1 22
#define led2 23
#define irSensor1 4
#define irSensor2 2

// Initializing some variables
int timer1 = 2;
int timer2 = 2;
int can = 0;
int bottle = 0;

BLECharacteristic *pCharacteristic;

// Callback class for BLE connection events
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("Device connected");
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("Device disconnected");
      BLEDevice::startAdvertising();
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);

  BLEDevice::init("eTracker_esp32");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  pCharacteristic->setValue("Initial Value");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  if(timer1 > 2){
    digitalWrite(led1, LOW);
  }

  if(timer2 > 2){
    digitalWrite(led2, LOW);
  }

  int sensorValue1 = analogRead(irSensor1);
  int sensorValue2 = analogRead(irSensor2);

  if(sensorValue1 < 300){
    timer1 = 0;
    digitalWrite(led1, HIGH);
    can++;
  }

  if(sensorValue2 < 300){
    timer2 = 0;
    digitalWrite(led2, HIGH);
    bottle++;
  }

  delay(500);
  timer1++;
  timer2++;

  // Update BLE characteristic with count values
  char valueStr[50];
  snprintf(valueStr, sizeof(valueStr), "can: %d, bottle: %d", can, bottle);
  pCharacteristic->setValue(valueStr);
  pCharacteristic->notify();
}