/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

#define NUM_TRACKS 4

Servo servos[2];  // create servo objects to control the servos

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// setup some constant, may need changing for your setup
const int start_button = 8;
const int hold_angle = 70;
const int release_angle = 0; 

// push buttons for the tracks;
const int tracks[NUM_TRACKS] = {A0, A1, A2, A3};

// which tracks have already finished
bool tracks_ready[NUM_TRACKS] = {true, true, true, true};
// times of the finished tracks
int tracks_times[NUM_TRACKS] = {-1,-1,-1,-1};
// number of tracks that are done
int tracks_done = 0;
// to keep track of time
unsigned long start_time = 0;

void setup() {
  pinMode(start_button, INPUT);
  lcd.begin(16, 2); 
  for(int i=0; i<NUM_TRACKS; i++){
      pinMode(tracks[i], INPUT);
  }
  servos[0].attach(9);
  servos[1].attach(10);
  servos[0].write(hold_angle);
  servos[1].write(release_angle);
}


void loop() {
  if (digitalRead(start_button)) {
    // start_button is pushed, clear the screen
    lcd.clear();
    start_time = micros();
    // release the balls!
    servos[0].write(release_angle);
    servos[1].write(hold_angle);
    for(int i = 0; i <= 3; ++i) {
      tracks_ready[i] = false;
    }
  }
  for (int i = 0; i < NUM_TRACKS; i++)
  {
    // if a ball reached the button, and has not already finished
    if (digitalRead(tracks[i]) &! tracks_ready[i]) {
      unsigned long timing = (micros() - start_time) / 1000; 
      tracks_ready[i] = true; 
      tracks_times[i] = timing;
      tracks_done++;
      servos[0].write(hold_angle);
      servos[1].write(release_angle);
    }
  }
  if (tracks_done >= NUM_TRACKS) {
    // All tracks have finished, print results to screen
    for (int i = 0; i < NUM_TRACKS; i++) {
      lcd.setCursor((i%2)*8, i>>1); 
      lcd.print('1' + i); 
      lcd.print(":"); 
      lcd.print(tracks_times[i]);
      lcd.print("ms");
    }
    tracks_done = 0;
  }
}
