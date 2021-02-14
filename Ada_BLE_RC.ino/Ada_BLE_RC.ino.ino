// Bluetooth imports

#include <Adafruit_ATParser.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_BLEEddystone.h>
#include <Adafruit_BLEGatt.h>
#include <Adafruit_BLEMIDI.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

#include <Adafruit_BLE_Firmata.h>
#include <Adafruit_BLE_Firmata_Boards.h>

#include <Adafruit_BLE_Firmata.h>
#include <Adafruit_BLE_Firmata_Boards.h>

#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"

#include "BluefruitConfig.h"

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

// motor driver import
//#include <AFMotor.h>

// Init motor object
//AF_DCMotor motor(1, MOTOR12_8KHZ);


// Name your RC here
String BROADCAST_NAME = "portable elevator";

String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

char buf[60];

// variables for loop
int velocity = 0;

float x, y;

int L_restrict = 0;
int R_restrict = 0;

unsigned long lastAccelPacket = 0;

bool modeToggle = false;

//-------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);     // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
//  motor.setSpeed(50);
 
//  motor.run(RELEASE);

  // set up bluetooth defined below
  BLEsetup();
}

void loop() {

//  motor.run(FORWARD);
//  delay(1000);  // run forward for 1 second
//  motor.run(RELEASE);
//  delay(100);  // 'coast' for 1/10 second
//  motor.run(BACKWARD);  // run in reverse
//  delay(100);  // 'coast' for 1/10 second

  static unsigned long lastPress = 0;
  bool isMoving = false;
  Serial.println(packetbuffer[1]);
  Serial.println(packetbuffer[2]);
  Serial.println(packetbuffer[3]);

  // Buttons
  if (packetbuffer[1] == 'B') {

    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    Serial.println("Made it to buttnum");

    if (pressed) {
      isMoving = true;
      if(buttnum == 5){
          Serial.println("f");
//        motor.run(FORWARD);
      }
      if(buttnum == 6){
//        motor.run(BACKWARD); 
          Serial.println("b"); 
      }

      lastPress = millis();
      } 
  
    else {
      isMoving = false;
//      motor.run(RELEASE);
        Serial.println("s");
    }
  }
}


void BLEsetup(){
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }

  //Convert the name change command to a char array
  BROADCAST_CMD.toCharArray(buf, 60);

  //Change the broadcast device name here!
  if(ble.sendCommandCheckOK(buf)){
    Serial.println("name changed");
  }
  delay(250);

  //reset to take effect
  if(ble.sendCommandCheckOK("ATZ")){
    Serial.println("resetting");
  }
  delay(250);

  //Confirm name change
  ble.sendCommandCheckOK("AT+GAPDEVNAME");

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("*****************"));

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("*****************"));
}
