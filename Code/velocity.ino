/*
 * LCD RS pin to digital pin 12//  22
 * LCD Enable pin to digital pin 11  /// 23
 * LCD D4 pin to digital pin 5//////  24
 * LCD D5 pin to digital pin 4///  25
 * LCD D6 pin to digital pin 3////  26
 * LCD D7 pin to digital pin 2///  27
 * LCD R/W pin to ground       /// 
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
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
# define Counter  30
# define Start 33
# define End 39
# define trig 37
int Count,Count_Read,Revo,Velocity;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

void setup() {
  pinMode(Counter, INPUT);
  pinMode(Start, INPUT);
  pinMode(End, INPUT);
   pinMode(trig, OUTPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Velocity");
  Count = 0;
  Count_Read=0;
  Velocity = 0;
  Revo = 0;
}

void loop() {
  
     if(Start == 1)
     {
       digitalWrite (trig, HIGH);
       RPM();
     }
     Revo = Count/40;
     Velocity = (2.2048*Revo + 0.0178)*0.3048; 
     digitalWrite (trig, LOW);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(Velocity);
}


void RPM(){
            while(1)
            {
                        Count_Read=digitalRead(Counter);
                        if(Count_Read == 1)
                            {
                                       Count= Count + 1;
                                       //delay(1000);
                            }
                             while(1)
                             {
                                         Count_Read = digitalRead(Counter);
                                         if(Count_Read == 1)
                                           {
                                           }
                                           else {
                                             break;
                                           }
                           }
                           if(End == 1)
                           {
                             break;
                           }
            }
          
}

