//install Library ultrasonik dulu dengan nama newping
//lihat di folder libraries

#include <Servo.h> // memanggil library servo
#include <NewPing.h> // memanggil library sensor ultrasonic

Servo myservo; // inisialisasi myservo
#define TRIGGER_PIN 9 // Pin Trigger dihubungkan ke Pin Digital 5 Arduino
#define ECHO_PIN 8 // Pin Echo dihubungkan ke pin Digital 6 Arduino
#define MAX_DISTANCE 90 // Batas jarak pengukuran sensor ultrasonic 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  myservo.attach(2); // Pin Out Servo dihubungkan ke Pin Digital 2 Arduino
  Serial.begin(9600);
}

void loop() {
delay(50); 
int jarak = sonar.ping_cm(); // Variabel "Jarak" untuk menampung hasil pengukuran jarak
Serial.println(jarak);
if((jarak>0)&&(jarak<=50))
  {
  delay(50); // jeda waktu 50 ms
  myservo.write(10); // Membuat servo berputar 10° (membuka kotak sampah)
  }
if((jarak>50)&&(jarak<=220))
  {
    delay(50);
    myservo.write(120);
  }
}
