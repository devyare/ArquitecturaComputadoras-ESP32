#include <Arduino.h>

const int LDR_PIN = 14;
const int LED_ROJO = 2;
const int LED_AMARILLO = 4;
const int LED_VERDE = 16;


const bool INVERTIR = false;

const int UMBRAL_BAJO = 1000;   // poca luz
const int UMBRAL_ALTO = 2800;   //  mucha luz

void setup() {
  Serial.begin(115200);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void loop() {
  int luz = analogRead(LDR_PIN);      // 0 a 4095
  if (INVERTIR) luz = 4095 - luz;

  digitalWrite(LED_ROJO, luz < UMBRAL_BAJO);
  digitalWrite(LED_AMARILLO, luz >= UMBRAL_BAJO && luz < UMBRAL_ALTO);
  digitalWrite(LED_VERDE, luz >= UMBRAL_ALTO);

  Serial.print("Valor de sensor: ");
  Serial.println(luz);
  delay(300);
}