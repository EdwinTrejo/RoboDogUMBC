//www.elegoo.com
//2016.12.08
#include <Servo.h>
#include "./ServoWithButton.h"

Leg::Leg(Servo primaryJoint, int pinPJ, Servo secondaryJoint, int pinSJ){
  primaryJoint.attach(pinPJ);
  secondaryJoint.attach(pinSJ);
  _primaryJoint = primaryJoint;
  _secondaryJoint = secondaryJoint;
}

void Leg::moveBy(int deg){
  _primaryJoint.write(deg);
  _secondaryJoint.write(deg);
}

void Leg::detachAll(){
  _primaryJoint.detach();
  _secondaryJoint.detach();
}

void Leg::stopAll(){
  _primaryJoint.write(0);
  _secondaryJoint.write(0);
}


// twelve servo objects can be created on most boards
Servo R_hind_leg;  // create servo object to control a servo for right leg
Servo L_hind_leg;  // create servo objectto control a servo for left leg
Leg leftHindLeg = Leg(R_hind_leg,9, L_hind_leg,10);
int buttonApin = 8;
int buttonBpin = 7;
int pos = 181;    // variable to store the servo position

//https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/
//we will look into gryo positioning depending on the gyro we have
//use this for scaling https://www.arduino.cc/en/Tutorial/Knob

void setup() {
   pinMode(buttonApin, INPUT_PULLUP);
   pinMode(buttonBpin, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(buttonApin) == HIGH) {
    leftHindLeg.moveBy(180);
    //for (pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      //R_hind_leg.write(pos);// tell servo to go to position in variable 'pos'
      //L_hind_leg.write(pos);// motor being filpped on left means position should work
      //delay(15);                       // waits 15ms for the servo to reach the position
    //}
  }
  if (digitalRead(buttonBpin) == HIGH){
      leftHindLeg.stopAll();
  }
  //R_hind_leg.detach();// tell servo to go to position in variable 'pos'
  //L_hind_leg.detach();// motor being filpped on left means position should work

  /*for (pos = 180; pos >= 0; pos -= 60) { // goes from 180 degrees to 0 degrees
    R_hind_leg.write(pos);// tell servo to go to position in variable 'pos'
    L_hind_leg.write(pos);// motor being filpped on left means position should work
    delay(15);                       // waits 15ms for the servo to reach the position
    }*/
}
