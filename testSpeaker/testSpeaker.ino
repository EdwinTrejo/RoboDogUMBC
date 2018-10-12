/*Arduino speaker song tutorial
* This program will play the theme song of the Malayalam movie
* 'Ennu Ninte Moideen'. The song is 'Mukkathe Penne'.
* The song is played on the speaker connected to pin 3 and GND.
* 
* Created 26 Oct 2015
* by Akshay James
* Video at https://www.youtube.com/watch?v=LgtcUxe8fmA
*/

#include"pitches.h"
#define SPEAKER 3

int melody[] = {
  1361, 689, 1798, 2063, 1127, 1237, 
  1361, 689, 1798, 2063, 1127, 1237, 
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237, 
  1361, 689, 1798, 2063, 1127, 1237, 
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,
  1361, 689, 1798, 2063, 1127, 1237,END
};

float noteDurations[] = {
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
  0.02, 0.02, 0.02, 0.02, 0.02, 0.02
};

/*// notes in the song 'Mukkathe Penne'
int melody[] = {
NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,                   
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                 

NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                       

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, 0,
NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, END

};

// note durations: 8 = quarter note, 4 = 8th note, etc.
int noteDurations[] = {       //duration of the notes
8,4,8,4,
4,4,4,12,
4,4,4,4,4,4,
4,16,4,

8,4,8,4,
4,2,1,1,2,1,1,12,
4,4,4,4,4,4,
4,16,4,

4,4,4,4,4,4,
4,4,4,12,
4,4,4,4,4,4,
4,4,4,12,

4,4,4,4,4,4,
2,1,1,2,1,1,4,8,4,
2,6,4,2,6,4,
2,1,1,16,4,

4,8,4,4,4,
4,16,4,
4,8,4,4,4,
4,20,
};
*/

// play tone on a piezo speaker: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl
 
void playTone(uint16_t tone1, uint16_t noteDuration) {
  noteDuration *= 4;
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < noteDuration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER, LOW);
     delayMicroseconds(tone1);
  }
  //tone(SPEAKER, tone1,noteDuration);

  //delay(noteDuration);

  //noTone(SPEAKER);
  
}

void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}
 
void arf() {    // dog arf
  uint16_t i;
  playTone(890,25);          // "a"    (short)
  for(i=890; i<910; i+=2)    // "rrr"  (vary down)
     playTone(i,5);
  playTone(4545,80);         // intermediate
  playTone(12200,70);        // "ff"   (shorter, hard to do)
}

int speed=90;  //higher value, slower notes
void setup() {

  Serial.begin(9600);
  /*for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

    int noteDuration = speed*noteDurations[thisNote];
    tone(3, melody[thisNote],noteDuration*.95);
    Serial.println(melody[thisNote]);

   delay(noteDuration);

   noTone(3);
  }*/
  for (int thisNote = 380; thisNote < 10000; thisNote++) {

   if(thisNote % 5 == 0) {
    int noteDuration = speed*0.02;
    tone(3, thisNote,noteDuration*.95);
    Serial.println(melody[thisNote]);

    delay(noteDuration);

    noTone(3);
   }
  }
  /*pinMode(SPEAKER,OUTPUT);  // important to set pin as output
  ruff();
  delay(2000);  
  arf();
  delay(2000);*/
}

void loop() {
// no need to repeat the melody.
}
