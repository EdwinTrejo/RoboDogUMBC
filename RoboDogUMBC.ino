#include <PID_v1.h>

#include "Adafruit_PWMServoDriver.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575// this is the 'maximum' pulse length count (out of 4096) // 600
#define MINANGLE  45
#define MAXANGLE  135

// our servo # counter
uint8_t servonum = 0;


double hAngle ;
double hNewAngle ;
double hDisplacement ;             // displacement angle
double vAngle ;
double vNewAngle ;
double vDisplacement ;             // displacement angle
const int MaxChars = 4;
char hstrValue[MaxChars+1];
int hindex = 0;
char vstrValue[MaxChars+1];
int vindex = 0;
boolean stringComplete = false;  // whether the string is complete
char inputString[MaxChars+1];         // a String to hold incoming data
int turn ;                       // indicates whether hAngle or hDisplacement is being updated; 0 for horizontal, 1 for vertical

/////////////////////PID VARS
//Define Variables we'll be connecting to
double h_Setpoint, h_Input, h_Output, v_Setpoint, v_Input, v_Output;

//Specify the links and initial tuning parameters
PID h_PID(&hAngle, &h_Output, &hNewAngle, 2,5,0, P_ON_M, DIRECT);
PID v_PID(&vAngle, &v_Output, &vNewAngle, 2,5,0, P_ON_M, DIRECT);
//////////////////////

// convAngle converts a requested angle (0-180) and converts it into pulse length for the servo
unsigned int convAngle(int angle) {
  long long num ;
  num = 31*angle/12 + SERVOMIN ;        // simplified numbers to avoid int overflows
  return num ;
}

void reset() {
  hAngle = 90 ;
  hNewAngle = 90 ;
  vAngle = 95 ;
  vNewAngle = 95 ;
  //Serial.println(itoa(hAngle,inputString,10));
  pwm.setPWM(0,0,convAngle(hAngle)) ;
  pwm.setPWM(1,0,convAngle(vAngle)) ;
  pwm.setPWM(2,0,convAngle(180 - vAngle)) ;
  int turn = 0 ;
}

void setup() {
  Serial.begin(9600);       // activate serial communication at 9600 baud
  //Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  /*hAngle = 90 ;
  vAngle = 95 ;
  Serial.println(itoa(hAngle,inputString,10));
  pwm.setPWM(0,0,convAngle(hAngle)) ;
  pwm.setPWM(1,0,convAngle(vAngle)) ;
  pwm.setPWM(2,0,convAngle(180 - vAngle)) ;
  int turn = 0 ;*/

  /////////////////////////PID
  //initialize the variables we're linked to
  reset() ;

  //turn the PID on
  h_PID.SetMode(AUTOMATIC);
  v_PID.SetMode(AUTOMATIC);

  h_PID.SetOutputLimits(-255, 255) ;    // specify min and max of PID output
  v_PID.SetOutputLimits(-255, 255) ;
  /////////////////////////////

  yield();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  //Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  //Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  //Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  /*// Drive each servo one at a time
  Serial.println(servonum);
  
  pwm.setPWM(0, 0, SERVOMAX);

  delay(500);
 
  pwm.setPWM(0, 0, SERVOMIN);

  delay(500);

  servonum ++;
  if (servonum > 7) servonum = 0;
  */
  // Detect serial input changes and send them to the servo
  while(Serial.available()) 
   {
      char ch = Serial.read();
      //Serial.write(ch);
      if(hindex < MaxChars && turn == 0 && (isDigit(ch) || (hindex == 0 && ch == '-'))) { 
            hstrValue[hindex++] = ch; 
      } 
      else if (ch == ' ') {               // space separates h and v vals
        turn = 1 ;
      }
      else if(ch == 'a') {                // reset to start position
        reset() ;
      }
      else if(vindex < MaxChars && turn == 1 && (isDigit(ch) || vindex == 0 && ch == '-')) { 
            vstrValue[vindex++] = ch; 
      }
      else { 
            hstrValue[hindex] = '\0';
            vstrValue[vindex] = '\0';
            //Serial.println(itoa(convAngle(atoi(hstrValue)),inputString,10));
            hDisplacement = atoi(hstrValue); 
            vDisplacement = atoi(vstrValue);

            // Set Horizontal Angle
            if(hAngle + hDisplacement >= MINANGLE && hAngle + hDisplacement <= MAXANGLE){
                   hNewAngle = hAngle + hDisplacement ;
            }
            else if(hAngle + hDisplacement < MINANGLE){
                   hNewAngle = MINANGLE ;
            }
            else if(hAngle + hDisplacement > MAXANGLE) {
                   hNewAngle = MAXANGLE ;
            }
            
            if(vAngle + vDisplacement >= MINANGLE && vAngle + vDisplacement <= MAXANGLE){
                   vNewAngle = vAngle + vDisplacement ;
            }
            else if(vAngle + vDisplacement < MINANGLE) {
                   vNewAngle = MINANGLE ;
            }
            else if(vAngle + vDisplacement > MAXANGLE) {
                   vNewAngle = MAXANGLE ;
            }

            //Serial.println(hNewAngle);
            //Serial.println(vNewAngle);
           
            /*h_PID.Compute();
            v_PID.Compute();
            Serial.println(h_Output);
            Serial.println(v_Output);
            Serial.println("-");

            pwm.setPWM(0,0,convAngle(hAngle + h_Output)) ;
            pwm.setPWM(1,0,convAngle(vAngle + v_Output)) ;
            pwm.setPWM(2,0,convAngle(180 - (vAngle + v_Output))) ;
            hAngle = hAngle + h_Output ;
            vAngle = vAngle + v_Output ;
            */
            hAngle = hNewAngle ;
            vAngle = vNewAngle ;
                    // pin num., idk, angle
            pwm.setPWM(0,0,convAngle(hAngle)) ;
            pwm.setPWM(1,0,convAngle(vAngle)) ;
            pwm.setPWM(2,0,convAngle(180 - (vAngle))) ;
            stringComplete = true ;
            
            vindex = 0;
            hindex = 0;
            turn = 0 ;
      }  
   }

  // print the string when a newline arrives:
  //if (stringComplete) {
  //  Serial.println(itoa(hAngle,inputString,10));
  //  Serial.println(itoa(vAngle,inputString,10));
  //  stringComplete = false;
  //}
}
