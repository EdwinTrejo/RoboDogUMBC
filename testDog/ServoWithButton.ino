//www.elegoo.com
//2016.12.08
#include <Servo.h>

Servo R_hind_leg;  // create servo object to control a servo for right leg
// twelve servo objects can be created on most boards
Servo L_hind_leg;  // create servo objectto control a servo for left leg
int buttonApin = 8;

int pos = 181;    // variable to store the servo position

void setup() {
  R_hind_leg.attach(9);  // attaches the servo on pin 9 to the servo object
  L_hind_leg.attach(10);  // attaches the servo on pin 8 to the servo object
  pinMode(buttonApin, INPUT_PULLUP);
}

void loop() {
  
  if(digitalRead(buttonApin) == HIGH) {
    for (pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      R_hind_leg.write(pos);// tell servo to go to position in variable 'pos'
      L_hind_leg.write(pos);// motor being filpped on left means position should work
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  //R_hind_leg.detach();// tell servo to go to position in variable 'pos'
  //L_hind_leg.detach();// motor being filpped on left means position should work
  
  /*for (pos = 180; pos >= 0; pos -= 60) { // goes from 180 degrees to 0 degrees
    R_hind_leg.write(pos);// tell servo to go to position in variable 'pos'
    L_hind_leg.write(pos);// motor being filpped on left means position should work
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
}
