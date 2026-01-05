/*
Type: Fixed Transmission
They are both a transmitter and a reciever (the ESP32 sends GPS data and Ping status to the Arduino)

Specficic message handling for each type of variable that will be changed through a structure (Documentation shows)

Encrypt the messages with a 2 way CRYPT key CRYPT_H and CRYPT_L
*/


#define REMOTEXY_MODE__SOFTSERIAL

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <RemoteXY.h>
#include <LoRa_E22.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600

// EBYTE's E22 pins
#define E22_M0 13
#define E22_M1 12
#define E22_RX 11
#define E22_TX 10
#define E22_AUX 9

SoftwareSerial loraSerial(E22_RX, E22_TX);
LoRa_E22 e22ttl(&loraSerial, E22_AUX, E22_M0, E22_M1);

#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =
  { 255,0,0,1,0,42,0,19,0,0,0,71,46,79,46,84,46,65,0,31,
  1,106,200,1,1,1,0,74,11,82,87,14,1,2,37,0,68,105,115,99,
  111,110,110,101,99,116,101,100,0 };
struct {
  uint8_t strings_01; // from 0 to 1

  uint8_t connect_flag;  // =1 if wire connected, else =0
} RemoteXY;   
#pragma pack(pop)

void setup() {
  Serial.begin(9600);
  
  // Initialize LoRa module
  loraSerial.begin(9600);

  if (e22ttl.begin())
    Serial.println(F("LoRa module initialized!"));
  else Serial.println(F("LoRa module failed to initialize!"));

  RemoteXY_Init(); 
}

void loop() { 
  RemoteXY_Handler ();

}