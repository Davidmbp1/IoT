#include <Arduino.h>

const int ldrPin = 33;
const int trigPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("LDR Value\tDistance (cm)");  // Encabezado de la tabla
}

void loop() {
  // Leer valor del LDR
  int ldrValue = analogRead(ldrPin);

  // Leer distancia del sensor HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.print(ldrValue);
    Serial.print("\t\t");
    Serial.println("Fuera de rango");
  } else {
    float distance = duration * 0.0343 / 2;
    Serial.print(ldrValue);
    Serial.print("\t\t");
    Serial.println(distance);
  }
  
  delay(1000);
}