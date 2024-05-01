#include <Servo.h>

Servo myservo;

#define ldr1 A6
#define ldr2 A7

int pos = 90;
int tolerance = 20;

void setup() {
  Serial.begin(9600); // Start serial communication
  myservo.attach(2);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  myservo.write(pos);
  delay(1000);
}

void loop() {      
  int val1 = analogRead(ldr1);
  int val2 = analogRead(ldr2);
      
  if ((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    // No servo motor movement if within tolerance
  } else {
    if (val1 > val2) {
      pos = pos + 1;
    }
    if (val1 < val2) {
      pos = pos - 1;
    }
  }
     
  if (pos > 180) {
    pos = 180;
  }
  if (pos < 0) {
    pos = 0;
  }
  myservo.write(pos);
  
  // Send sensor data over serial
  Serial.print(val1);
  Serial.print(",");
  Serial.println(val2);
  
  delay(50);
}