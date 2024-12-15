#include <Servo.h>
Servo myservo;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(2);
  myservo.write(90);
  delay(1000);
  myservo.detach();
  delay(5000);

}

void loop() { // run over and over
  while (mySerial.available() > 0) {
    String data = mySerial.readString();
    Serial.println(data);
    if (data == "R") {
      myservo.attach(2);
      myservo.write(20);
      delay(250);
      myservo.detach();
      delay(500);
    }
    else if (data == "L") {
      myservo.attach(2);
      myservo.write(160);
      delay(500);
      myservo.detach();
      delay(250);
    }
    else if (data == "G") {
      myservo.attach(2);
      myservo.write(90);
      delay(500);
      myservo.detach();
      delay(500);
    }
    else if (data == "F") {
      myservo.attach(2);
      myservo.write(90);
      delay(500);
      myservo.detach();
      delay(500);
    }
  }
}
