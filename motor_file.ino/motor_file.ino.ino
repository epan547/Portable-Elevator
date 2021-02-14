#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(1,0);
// motor driver import
#include <AFMotor.h>


int current_floor= 2;
//AF_DCMotor motor(1, MOTOR12_8KHZ);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(38400);
  
}

char buf[2];

void loop() {
  if (Bluetooth.available() > 0) {
    Serial.print("are we here?");
    Bluetooth.print("maybe?");
    String x = Bluetooth.readString();
    Serial.println(x);
    Serial.readBytes(buf, 2);
    Serial.println(buf[0]);
    delay(500);
    if (buf[1]-'0' == 5) {
      Serial.println("Move forward");
    }
    if (buf[1]-'0' == 6) {
      Serial.println("Move backwards");
    }
  }
  else {
//    Serial.println("Serial not available");
    Serial.flush();
  }
  
}
