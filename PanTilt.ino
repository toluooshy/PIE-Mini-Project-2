/* PanTilt
 
*/

#include <Servo.h>

const int analogInPin = A0;  // Analog input pin that the IR Sensor is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

Servo servo1;  // create servo object to control the panning servo
Servo servo2;  // create servo object to control the tilting servo

int pos1 = 90;    // variable to store servo1's position
int pos2 = 90;    // variable to store servo2's position

void setup() {
  Serial.begin(9600);
  Serial.print("pos1 (panning on x-axis)"); Serial.print(",");
  Serial.print("pos2 (tilting on y-axis)"); Serial.print(",");
  Serial.print("sensor"); Serial.print(",");
  Serial.print("output"); Serial.print(",");
  Serial.print('\n');
  
  servo1.attach(12);  // attaches the panning servo on pin 12 to the servo object
  servo2.attach(13);  // attaches the tilting servo on pin 13 to the servo object
}


void loop() {
  while(pos1 <= 125) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degrees
    servo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    while(pos2 <= 115) {
      servo2.write(pos2);
      readsensor();
      delay(15);
      pos2 += 1;
    }
    while (pos2 >= 55) {
      servo2.write(pos2);
      readsensor();
      delay(15);
      pos2 -= 1;
    }
    pos1 += 5;
  }
  while(pos1 >= 55) { // goes from 180 degrees to 0 degrees
    // in steps of 1 degrees
    servo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    while(pos2 <= 115) {
      servo2.write(pos2);
      readsensor();
      delay(15);
      pos2 += 1;
    }
    while (pos2 >= 55) {
      servo2.write(pos2);
      readsensor();
      delay(15);
      pos2 -= 1;
    }
    pos1 -= 5;
  }
}

void readsensor() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  Serial.print(pos1); Serial.print(",");
  Serial.print(pos2); Serial.print(",");
  Serial.print(sensorValue); Serial.print(",");
  Serial.print(outputValue); Serial.print(",");
  Serial.println("");

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
