#include<LiquidCrystal.h>
LiquidCrystal lcd(41,42,44,45,46,47);
const int inPin = 0;
void setup()
{
lcd.begin(16,2);
}
void loop()
{
int value = analogRead(inPin);
lcd.setCursor(0,1);
float millivolts = (value/1024.0)*5000;
float celsius = millivolts/10;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temp = ");
lcd.print(celsius);
lcd.print("Cel");
delay(100);
lcd.setCursor(0,1);
}
