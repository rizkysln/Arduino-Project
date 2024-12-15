#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
#define led1 2 //hijau
#define led2 3 //kuning
#define led3 4 //merah
#define buzzer 5


void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(buzzer,OUTPUT); 
  lcd.init();                 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Alat  Pendeteksi");
  lcd.setCursor(5,1);
  lcd.print("Banjir");
  lcd.display();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alat  Pendeteksi");
  lcd.setCursor(1,1);
  lcd.print("by:rizky solin");
  lcd.display();
  delay(3000);
  lcd.clear();
}

void loop() {
  delay(400);
  lcd.clear();
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  lcd.setCursor(0,0); 
  lcd.print("JARAK: "); 
  lcd.setCursor(7,0); 
  lcd.print(sonar.ping_cm()); 
  lcd.setCursor(10,0); 
  lcd.print("cm"); 
  Serial.println("cm");
  if((sonar.ping_cm()>1)&&(sonar.ping_cm()<=15)){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,1);
    lcd.print("banjiiirr!!!");
  }
  else if((sonar.ping_cm()>10)&&(sonar.ping_cm()<=18)){
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    digitalWrite(buzzer,LOW);
    lcd.setCursor(0,1);
    lcd.print("waspadaa!!!");
  }
  else if((sonar.ping_cm()>15)&&(sonar.ping_cm()<=20)){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW); 
    digitalWrite(led3,LOW);
    digitalWrite(buzzer,LOW);
    lcd.setCursor(0,1);
    lcd.print("amaaaan");
  }
  else{
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(buzzer,LOW);
    lcd.setCursor(0,1);
    lcd.print("aman");
  }    
}
  
