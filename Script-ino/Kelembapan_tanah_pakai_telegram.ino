#include "CTBot.h"
CTBot myBot;

// WiFi credentials
String ssid = "STARLIGHT"; // GANTI DENGAN SSID WIFI ANDA
String pass = "STARLIGHt"; // GANTI DENGAN PASSWORD WIFI ANDA
String token = "7667888656:AAFIh4HTOjqO1lSNcKM00iKF6ooQLZHD-Ho"; // GANTI DENGAN TOKEN BOT TELEGRAM ANDA

// Pin sensor dan relay
#define SOIL_SENSOR_PIN A0
#define RELAY_PIN D1 

// Batas kelembapan tanah (nilai ADC 645 = basah, 1023 = kering)
#define MOISTURE_THRESHOLD 800 // Sesuaikan ambang batas untuk kondisi kering

void setup() {
  Serial.begin(9600);
  Serial.println("Memulai TelegramBot...");

  // Inisialisasi sensor dan relay
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Matikan pompa di awal

  // Hubungkan ke WiFi
  myBot.wifiConnect(ssid, pass);

  // Atur token bot Telegram
  myBot.setTelegramToken(token);

  // Periksa koneksi bot Telegram
  if (myBot.testConnection()) {
    Serial.println("\ntestConnection OK");
  } else {
    Serial.println("\ntestConnection NOK");
  }
}

void loop() {
  // Baca nilai sensor kelembapan tanah
  int soilMoisture = analogRead(SOIL_SENSOR_PIN);
  Serial.print("Kelembapan Tanah (ADC): ");
  Serial.println(soilMoisture);

  // Konversi nilai ADC menjadi persentase (645-1023 ke 100%-0%)
  int moisturePercentage = map(soilMoisture, 1023, 645, 0, 100);

  // Flag untuk memastikan notifikasi hanya dikirim sekali
  static bool notifiedDry = false;

  // Periksa kondisi tanah
  if (soilMoisture > MOISTURE_THRESHOLD) { // Tanah kering
    Serial.println("Tanah kering, mengaktifkan pompa air...");
    digitalWrite(RELAY_PIN, HIGH); // Hidupkan pompa

    // Kirim notifikasi jika belum dikirim
    if (!notifiedDry) {
      String message = "Tanah kering terdeteksi!\n"
                       "Kelembapan: " + String(moisturePercentage) + 
                       "%\nPompa air telah dihidupkan.";
      myBot.sendMessage(5383352245, message);
      Serial.println("Pesan Terkirim:\n" + message);
      notifiedDry = true; // Tandai bahwa notifikasi telah dikirim
    }
  } else { // Tanah cukup lembap
    Serial.println("Tanah cukup lembap, mematikan pompa...");
    digitalWrite(RELAY_PIN, LOW); // Matikan pompa
    notifiedDry = false; // Reset flag notifikasi
  }

  // Periksa pesan masuk dari Telegram
  TBMessage msg;
  if (CTBotMessageText == myBot.getNewMessage(msg)) {
    String message = msg.text;
    Serial.println("Pesan Diterima: " + message);

    // Jika pesan adalah "/cek"
    if (message == "/cek") {
      String response = "Kelembapan Tanah Saat Ini: " + String(moisturePercentage) + "%";
      myBot.sendMessage(msg.sender.id, response);
      Serial.println("Pesan Terkirim:\n" + response);
    }

    // Jika pesan adalah "/siram"
    if (message == "/siram") {
      myBot.sendMessage(msg.sender.id, "Air dihidupkan selama 2 detik.");
      Serial.println("Pompa air dihidupkan selama 2 detik.");
      digitalWrite(RELAY_PIN, HIGH); // Hidupkan relay
      delay(2000);                   // Tunggu 2 detik
      digitalWrite(RELAY_PIN, LOW);  // Matikan relay
      myBot.sendMessage(msg.sender.id, "Penyiraman selesai.");
      Serial.println("Pompa air dimatikan.");
    }
  }

  // Tunggu 500ms sebelum iterasi berikutnya
  delay(500);
}
