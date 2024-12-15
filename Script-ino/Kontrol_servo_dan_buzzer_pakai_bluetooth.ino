#include <Servo.h>
Servo myservo;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#define klakson 12

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(klakson, OUTPUT);
  digitalWrite(klakson,LOW);
  myservo.attach(3);
  myservo.write(0);
  delay(1000);
  myservo.detach();
  delay(1000);
}

void loop() { // run over and over
  if (mySerial.available())
  {
    char data = mySerial.read();
    Serial.println(data);
    switch (data)
    {
      case'A': myservo.attach(3);
               myservo.write(90);
               delay(500);
               myservo.detach();
               delay(500); 
               break;
      case'B': myservo.attach(3);
               myservo.write(0);
               delay(500);
               myservo.detach();
               delay(250); 
               break;
      case'H': digitalWrite(klakson,HIGH);
               break;
      case'I': digitalWrite(klakson,LOW);
               break;        
      default: break;
    }
  }
}

