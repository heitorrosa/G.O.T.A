#include <Arduino.h>
#include <HardwareSerial.h>
#include <LoRa_E22.h>

// EBYTE's E22 pins (UART2: GPIO17=TX, GPIO16=RX)
#define E22_M0 13
#define E22_M1 12
#define E22_RX 16
#define E22_TX 17
#define E22_AUX 14

HardwareSerial loraSerial(2);
LoRa_E22 e22ttl(&loraSerial, E22_AUX, E22_M0, E22_M1);

void setup() {
  Serial.begin(9600);

  // Initialize the LoRa module
  loraSerial.begin(9600, SERIAL_8N1, E22_RX, E22_TX);
  
  if (e22ttl.begin())
    Serial.println(F("LoRa module initialized!"));
  else Serial.println(F("LoRa module failed to initialize!"));

  
}

void loop() {
  delay(1000);
}