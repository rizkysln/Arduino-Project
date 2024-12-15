int sensorSuara = A0;
int pinLED = 13;
boolean kondisi = 0; // Kondisi LED, 0 = mati, 1 = menyala

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(sensorSuara, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorSuara);
  Serial.println(sensorValue);

  if (kondisi == 0 && sensorValue > 100) {
    // Suara pertama terdeteksi, nyalakan LED
    digitalWrite(pinLED, HIGH);
    kondisi = 1; // Ubah kondisi menjadi menyala
    Serial.println("Terdeteksi Suara Frekuensi Tinggi - LED ON");
    delay(300); // Tunggu sejenak untuk menghindari noise deteksi ganda
  } else if (kondisi == 1 && sensorValue > 100) {
    // Suara kedua terdeteksi, matikan LED
    digitalWrite(pinLED, LOW);
    kondisi = 0; // Ubah kondisi menjadi mati
    Serial.println("Terdeteksi Suara Frekuensi Tinggi - LED OFF");
    delay(300); // Tunggu sejenak untuk menghindari noise deteksi ganda
  }

  delay(100); // Delay untuk stabilisasi pembacaan sensor
}