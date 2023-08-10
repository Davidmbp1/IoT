// Incluye la biblioteca para el ESP32
#include <Arduino.h>

// Define el pin ADC que estás utilizando (GPIO04)
const int ldrPin = 33;

void setup() {
  // Inicializa el puerto serial
  Serial.begin(19200);

  // Configura el pin ADC como entrada
  pinMode(ldrPin, INPUT);
}

void loop() {
  // Lee el valor analógico del pin ADC (rango: 0-4095)
  int ldrValue = analogRead(ldrPin);

  // Imprime el valor leído en el puerto serial
  Serial.print("Valor del LDR: ");
  Serial.println(ldrValue);

  // Espera un breve período antes de la siguiente lectura
  delay(1000);
}