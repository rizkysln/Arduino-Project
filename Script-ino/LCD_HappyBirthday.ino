#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
}


void loop() {
  lcd.setCursor(3,0);
  lcd.print("HAPPY");
  lcd.setCursor(1,1);
  lcd.print("BIRTHDAY!!");
  lcd.scrollDisplayLeft();
  delay(500);
  
}
