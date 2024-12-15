#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#define Relay 12

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
}

void loop() { // run over and over
  while (mySerial.available() > 0) {
    char data = mySerial.read();
    Serial.println(data);
    switch (data)
    {
      case 'G': digitalWrite(Relay, LOW);
        break;
      case 'H': digitalWrite(Relay, HIGH);
        break;
      default : break;
    }
  }
}
