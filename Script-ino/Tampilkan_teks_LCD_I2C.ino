#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int standbyPin = 2; // Pin D2 untuk standby

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(standbyPin, OUTPUT); // Atur D2 sebagai output
  digitalWrite(standbyPin, HIGH); // Set D2 ke high
}

void loop() {
  lcd.setCursor(1, 1);
  lcd.print("SELAMAT DATANG");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(1, 0);
  lcd.print("SELAMAT DATANG");
  lcd.setCursor(4, 1);
  lcd.print("DI DESA");
  delay(2000);
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("DI DESA");
  lcd.setCursor(1, 1);
  lcd.print("GUNUNG SELAMAT");
  delay(2000); 
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("PROJECT by:");
  lcd.setCursor(4, 1);
  lcd.print("Rizkysln_");
  delay(2000); 
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("Rizkysln_");
  delay(2000); 
  lcd.clear();
}
