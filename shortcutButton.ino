/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

 /*Benjamin Gahle - DIY Shortcut Button
  * tinker-fun.com
  * 72mhz
  */
  
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include "OneButton.h"


//Shortcuts
String doubleClick = "b";
String turnRight = "9";
String turnLeft = "0";
String turnRight1 = "+";
String turnLeft1 = "-";

int counter = 0;

OneButton button(1, true);

unsigned long timer;

bool doubleTab;
long newPosition;
bool buttonState = false;
bool on;
bool off;

int led = 4;
Encoder myEnc(2, 3);


void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  int x;
  for(x=0; x <= 255; x++)
  {
    analogWrite(led,x);
    delay(2);
  }

  button.attachClick(myClickFunction);
  button.attachDoubleClick(doubleclick);
  
  button.attachLongPressStart(longPressStart);
  button.attachLongPressStop(longPressStop);
//button.attachDuringLongPress(longPress);
 
}

long oldPosition  = -999;

void loop() {
    button.tick();
    delay(10);
    leftRight();
    ledMode();
  }


void myClickFunction()
{
 buttonState = !buttonState; 
 ledMode();
}

void doubleclick() {
  
Keyboard.print(doubleClick);
} 

void longPressStart() {
  Serial.println("Button 1 longPress...");
  Keyboard.set_key1(KEY_SPACE);
  Keyboard.send_now();
}

// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop() {
  Serial.println("Button 1 longPress stop");
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void ledMode()
{
 if (buttonState == true && millis() - timer < 200 && off == false)
  {    
    off = true;
    on = false;
    ledOff();  
    //Serial.println("led off");
  }

    if (buttonState == true && millis() - timer > 200 && millis() - timer < 1000 && on == false)
  {
    on = true;
    off = false;
    ledOn();  
   // Serial.println("led on");
  }

    if (buttonState == true && millis() - timer > 1000)
  {  
    timer = millis();    
  }
  
  if(buttonState == false)
  {
    analogWrite(led,255);  
  }
}

void leftRight()
{     
   newPosition = myEnc.read();

   if (newPosition != oldPosition && counter == 0)
  {
    counter++;
   //Serial.println(counter);
   //Serial.println(newPosition);
   //Serial.println(oldPosition);
   oldPosition = newPosition;
  }

    if (newPosition != oldPosition && counter == 1)
  {
    counter++;
   //Serial.println(counter);
   //Serial.println(newPosition);
   //Serial.println(oldPosition);
   //oldPosition = newPosition;
  }

    if (counter == 2 && buttonState == false) {
 
    if(newPosition < oldPosition)
    {
     Serial.println("right");
     Keyboard.print(turnRight);        
    }

    if(newPosition > oldPosition)
    {
     Serial.println("left");
     Keyboard.print(turnLeft);     
     }
  
   //counter = 0;
//     Serial.println(newPosition);
//     Serial.println(oldPosition); 
// Serial.println("test");

  oldPosition = newPosition;
  counter = 0;   
  }


  //if (newPosition != oldPosition && buttonState == true) {
 if (counter == 2 && buttonState == true) {
    
  
    if(newPosition < oldPosition)
    {
     Serial.println("zoom in");
     Keyboard.print(turnRight1);
     }

    if(newPosition > oldPosition)
    {
     Serial.println("zoom out");
     Keyboard.print(turnLeft1);
     }  

    oldPosition = newPosition;
    counter = 0;
  }
}

void ledOff()
{
  //analogWrite(led, 0);
  int y;
  for(y = 255; y > 100; y--)
  {
    analogWrite(led,y);
    delay(1);
  }
}

void ledOn()
{
 // analogWrite(led, 255);
   int y;
  for(y = 100; y < 255; y++)
  {
    analogWrite(led,y);
    delay(1);
  }
}

