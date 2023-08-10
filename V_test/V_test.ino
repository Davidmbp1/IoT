#include <Arduino.h>

const int potPin = 34;  // Pin conectado al potenciómetro
const float referenceVoltage = 3.3;  // Voltaje de referencia del ESP32 (en V)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(potPin);
  float voltage = (adcValue / 4095.0) * referenceVoltage;  // Convertir valor ADC a voltaje
  
  Serial.print("Valor ADC: ");
  Serial.print(adcValue);
  Serial.print("\t");
  Serial.print("Voltaje: ");
  Serial.print(voltage, 2);  // Mostrar el voltaje con 2 decimales
  Serial.println(" V");

  delay(1000);  // Esperar un segundo antes de la siguiente lectura
}