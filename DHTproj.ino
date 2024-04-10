#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4       //  Kojele  #4 ant ESP8266
#define DHTTYPE DHT22  // Sensorio tipas

const char* ssid = "Galaxy"; // SSID vardas
const char* password = ""; // Wifi slaptazodis
const char* serverName = "api.thingspeak.com"; // I kur siunciame serverio vardas

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature_C, temperature_F;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop() {
  delay(2000);
  temperature_C = dht.readTemperature();
  temperature_F = dht.readTemperature(true);
  humidity = dht.readHumidity();
  // Tikrina ar nera problemos nuskaitant 
  if (isnan(humidity) || isnan(temperature_C) || isnan(temperature_F)) {
    Serial.println("DHT reading failed");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Temperature:");
  Serial.print(temperature_C);
  Serial.print(("°C ------- "));
  Serial.print(temperature_F);
  Serial.println("°F");
  
  WiFiClient client;
  HTTPClient http;
  String url = "http://" + String(serverName) + 
  "/update?api_key=0MGB9TQDG8YI7NNK&field2=" + String(humidity) 
  + "&field1=" + String(temperature_C) 
  + "&field3=" + String(temperature_F);
  Serial.println(url);
  http.begin(client, url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }
  http.end();
}
