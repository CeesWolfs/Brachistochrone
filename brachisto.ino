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

Servo myservo;  // create servo object to control a servo
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int startknop = 7;

const int servopin = 6;
const int vasthoek = 50;
const int loslaathoek = 120; 

const int baan1 = 13;
const int baan2 = 8;
const int baan3 = 9;
const int baan4 = 10;

bool klaar1 = false;
bool klaar2 = false;
bool klaar3 = false;
bool klaar4 = false;

unsigned long starttime;
bool running = false;

void setup() {
  pinMode(startknop, INPUT);
  pinMode(baan1, INPUT);
  pinMode(baan2, INPUT);
  pinMode(baan3, INPUT);
  pinMode(baan4, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // set up the servo's
  myservo.attach(servopin);
}

void loop() {
  if (digitalRead(startknop)) {
    // startknop is ingedrukt
    lcd.setCursor(0,0);
    lcd.print("Ready?, GO!");
    // draai de servos
    starttime = millis();
    running = true;
    myservo.write(loslaathoek);
  }
  if (running) {
    // Balletjes zijn aan het rollen
    lcd.setCursor(0, 1);
    lcd.print(millis() - starttime);
    lcd.print("ms");
  }
  if (digitalRead(baan1) &! klaar1) {int timing = millis() - starttime; klaar2 = true; if(running) {lcd.clear(); running = false; myservo.write(loslaathoek); } lcd.setCursor(0,0); lcd.print("1:"); lcd.print(timing);}
  if (digitalRead(baan2) &! klaar2) {int timing = millis() - starttime; klaar2 = true; if(running) {lcd.clear(); running = false; myservo.write(loslaathoek); } lcd.setCursor(0,8); lcd.print("2:"); lcd.print(timing);}
  if (digitalRead(baan3) &! klaar3) {int timing = millis() - starttime; klaar3 = true; if(running) {lcd.clear(); running = false; myservo.write(loslaathoek); } lcd.setCursor(1,0); lcd.print("3:"); lcd.print(timing);}
  if (digitalRead(baan4) &! klaar4) {int timing = millis() - starttime; klaar4 = true; if(running) {lcd.clear(); running = false; myservo.write(loslaathoek); } lcd.setCursor(1,8); lcd.print("4:"); lcd.print(timing);}

}
