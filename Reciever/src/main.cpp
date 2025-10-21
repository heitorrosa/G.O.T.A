#include <Arduino.h>
#include <HardwareSerial.h>
#include <LoRa_E22.h>

// ESP32 pins for LoRa module (UART2: GPIO17=TX, GPIO16=RX)
#define E22_M0 13
#define E22_M1 12
#define E22_RX 16
#define E22_TX 17
#define E22_AUX 14

// Create hardware serial for LoRa module (UART2 on ESP32)
HardwareSerial loraSerial(2);

// Initialize E22 module
LoRa_E22 e22(&loraSerial, E22_AUX, E22_M0, E22_M1);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println(F("\n\n--- ESP32 E22 LoRa Module Basic Test ---"));
  
  // Initialize LoRa module
  loraSerial.begin(9600, SERIAL_8N1, E22_RX, E22_TX);
  delay(100);
  
  if (e22.begin()) {
    Serial.println(F("✓ E22 initialization successful!"));
    Serial.println(F("✓ LoRa module is working!"));
  } else {
    Serial.println(F("✗ E22 initialization failed!"));
  }
}

void loop() {
  delay(1000);
}