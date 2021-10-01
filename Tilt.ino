/* Tilt
 
*/

#include <Servo.h>

const int analogInPin = A0;  // Analog input pin that the IR Sensor is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

Servo servo1;  // create servo object to control the tilting servo

int pos1 = 90;    // variable to store servo1's position

void setup() {
  Serial.begin(9600);
  Serial.print("pos1 (tilting on y-axis)"); Serial.print(",");
  Serial.print("sensor"); Serial.print(",");
  Serial.print("output"); Serial.print(",");
  Serial.print('\n');
  
  servo1.attach(13);  // attaches the tilting servo on pin 13 to the servo object
}


void loop() {
  while(pos1 <= 115) {
    servo1.write(pos1);
    readsensor();
    delay(15);
    pos1 += 1;
  }
  while (pos1 >= 55) {
    servo1.write(pos1);
    readsensor();
    delay(15);
    pos1 -= 1;
  }
}

void readsensor() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  Serial.print(pos1); Serial.print(",");
  Serial.print(sensorValue); Serial.print(",");
  Serial.print(outputValue); Serial.print(",");
  Serial.println("");

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
