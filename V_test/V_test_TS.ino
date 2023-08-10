#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

//Casa
// const char *ssid = "NATALY";        
// const char *password = "8182181AB";   

//IL
const char *ssid = "UNI_LIBRE_H"; 
const char *password = "123456789";

const char *server = "api.thingspeak.com";
const String apiKey = "45AP4F57Z6A6T5QZ"; // Cambia esto a tu clave API de ThingSpeak

const int potPin = 34;
const float referenceVoltage = 3.3;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
}

void loop() {
  int adcValue = analogRead(potPin);
  float voltage = (adcValue / 4095.0) * referenceVoltage;

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://";
    url += server;
    url += "/update?api_key=";
    url += apiKey;
    url += "&field1=";
    url += String(adcValue);
    url += "&field2=";
    url += String(voltage, 2);

    Serial.print("Enviando datos a ThingSpeak... ");
    Serial.println(url);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... código de estado: %d\n", httpCode);
    } else {
      Serial.printf("[HTTP] GET... fallo, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("Error de conexión WiFi");
  }

  delay(15000);  // Esperar 15 segundos antes de la siguiente lectura y envío
}