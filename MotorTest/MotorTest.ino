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
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_8KHZ);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(50);
 
  motor.run(RELEASE);
}

void loop() {

  motor.run(FORWARD);
  delay(1000);  // run forward for 1 second
  motor.run(RELEASE);
  delay(100);  // 'coast' for 1/10 second
  motor.run(BACKWARD);  // run in reverse
  delay(100);  // 'coast' for 1/10 second

//  uint8_t i;
//  
//  Serial.print("tick");
//  
//  motor.run(FORWARD);
//  for (i=0; i<255; i++) {
//    motor.setSpeed(i);  
//    delay(10);
// }
// 
//  for (i=255; i!=0; i--) {
//    motor.setSpeed(i);  
//    delay(10);
// }
//  
//  Serial.print("tock");
//
//  motor.run(BACKWARD);
//  for (i=0; i<255; i++) {
//    motor.setSpeed(i);  
//    delay(10);
// }
// 
//  for (i=255; i!=0; i--) {
//    motor.setSpeed(i);  
//    delay(10);
// }
//  
//
//  Serial.print("tech");
//  motor.run(RELEASE);
//  delay(1000);
}
