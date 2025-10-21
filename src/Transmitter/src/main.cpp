#define REMOTEXY_MODE__SOFTSERIAL

#include <Arduino.h>
#include <RemoteXY.h>
#include <SoftwareSerial.h>
#include <LoRa_E22.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600

// General definitions of pins
#define E22_M0 13
#define E22_M1 12
#define E22_RX 11
#define E22_TX 10
#define E22_AUX 9

// Create software serial for LoRa module
SoftwareSerial loraSerial(E22_RX, E22_TX);

// Initialize E22 module
LoRa_E22 e22(&loraSerial, E22_AUX, E22_M0, E22_M1);

#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =
  { 255,1,0,3,0,43,0,19,0,0,0,71,46,79,46,84,46,65,0,31,
  1,106,200,1,1,2,0,10,23,107,61,61,48,4,26,31,79,78,0,31,
  79,70,70,0,65,28,29,54,54,112 };
  
struct {

    // input variables
  uint8_t pushSwitch_01; // =1 if state is ON, else =0, from 0 to 1

    // output variables
  uint8_t led_01_r; // =0..255 LED Red brightness, from 0 to 255
  uint8_t led_01_g; // =0..255 LED Green brightness, from 0 to 255
  uint8_t led_01_b; // =0..255 LED Green brightness, from 0 to 255

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void setup() 
{
  Serial.begin(9600);
  delay(500);
  
  Serial.println(F("\n\n--- Arduino E22 LoRa Module Basic Test ---"));
  
  // Initialize LoRa module
  loraSerial.begin(9600);
  delay(100);
  
  if (e22.begin()) {
    Serial.println(F("✓ E22 initialization successful!"));
    Serial.println(F("✓ LoRa module is working!"));
  } else {
    Serial.println(F("✗ E22 initialization failed!"));
  }
  
  RemoteXY_Init(); 

}

void loop() 
{ 
  RemoteXY_Handler ();

}