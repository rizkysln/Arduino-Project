#include <NewPing.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  Serial.begin(9600); 
  lcd.setCursor(2,0);
  lcd.print("Rizky Proyek");
  lcd.display();
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  
  
  
}
void loop() {
  lcd.setCursor(1,0);
  lcd.print("Air Akan Penuh");
  lcd.setCursor(3,1);
  lcd.print("Dalam: ");
  lcd.setCursor(9,1);
  lcd.print(sonar.ping_cm());
  Serial.println(sonar.ping_cm());
  lcd.setCursor(11,1);
  lcd.print("cm");
  
  delay(500);
  lcd.clear();
}
