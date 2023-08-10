#include <Arduino.h>

const int trigPin = 12;
const int echoPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000); // Incrementa el tiempo máximo a 30000 microsegundos (30 ms)
  // Velocidad del sonido 343 m/s (0.0343 cm/μs)
  float dist = duration * 0.0343 / 2;

  if (duration == 0) {
    Serial.println("Fuera de rango"); // Imprime un mensaje si la duración es 0
  } else {
    Serial.print("Distancia: ");
    Serial.print(dist);
    Serial.println(" cm");
  }

  delay(1000);
}