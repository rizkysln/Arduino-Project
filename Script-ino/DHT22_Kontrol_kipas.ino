#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define RELAY_PIN 3  // Pin connected to the relay

// Uncomment the type of DHT sensor you're using
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 test with relay control!"));

  dht.begin();

  // Set the relay pin as output
  pinMode(RELAY_PIN, OUTPUT);

  // Ensure the relay starts in the LOW state (off)
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature in Celsius

  // Check if any reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display the results
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C"));

  // Control the relay based on temperature
  if (t > 31.0) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    Serial.println(F("Relay is ON (HIGH) - Temperature exceeds 32°C"));
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    Serial.println(F("Relay is OFF (LOW) - Temperature is below or equal to 32°C"));
  }
}
