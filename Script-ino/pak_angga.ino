#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN 12  // GPIO0 (D3)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "SMART_HOME.";
const char* password = "serumpunkasiH";
String GOOGLE_SCRIPT_ID = "AKfycbzA9i-DKvcnF8zrN88rlkxJN1qwPai_it64XIrwt90CB_nVcSFqzQMTxdn6PrTDbjk2";

bool lastButtonState = HIGH;  // Simpan state tombol terakhir
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // Delay debounce 50ms

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Gunakan internal pull-up
  lcd.init();
  lcd.backlight();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Menghubungkan ke Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n✅ WiFi Terhubung!");
  lcd.clear();
  lcd.print("WiFi Connected!");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Cek apakah tombol berubah state (HIGH ke LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    unsigned long currentTime = millis();
    
    // Debounce
    if (currentTime - lastDebounceTime > debounceDelay) {
      Serial.println("\n📡 Tombol ditekan! Mengambil data...");
      bacaGoogleSheet();
      lastDebounceTime = currentTime;
    }
  }

  lastButtonState = buttonState;  // Update state terakhir
}

void bacaGoogleSheet() {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();

  HTTPClient https;
  String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?read";
  
  https.begin(*client, url.c_str());
  https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  int httpCode = https.GET();
  Serial.print("📶 HTTP Status Code: ");
  Serial.println(httpCode);

  if (httpCode > 0) {
    String payload = https.getString();
    Serial.println("📩 Payload diterima:");
    Serial.println(payload);

    // Parsing JSON
    int idxQt = payload.indexOf("total_quantity\":") + 16;
    int idxTtl = payload.indexOf("total_belanja\":") + 15;
    int endIdxQt = payload.indexOf(",", idxQt);
    int endIdxTtl = payload.indexOf("}", idxTtl);

    String totalQt = payload.substring(idxQt, endIdxQt);
    String totalTtl = payload.substring(idxTtl, endIdxTtl);

    // Tampilkan ke LCD
    lcd.clear();
    
    // Baris 1: Total Belanja
    lcd.setCursor(0, 0);
    lcd.print("Ttl: " + totalTtl);

    // Baris 2: Total Quantity
    lcd.setCursor(0, 1);
    lcd.print("Qt: " + totalQt);
  } else {
    Serial.println("❌ Gagal mengambil data!");
    lcd.clear();
    lcd.print("Error Fetching Data");
  }

  https.end();
}
