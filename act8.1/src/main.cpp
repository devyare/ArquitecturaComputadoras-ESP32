#include <Arduino.h>

const uint8_t buttonPin = 2;
const uint8_t outputPin = 4;
const uint8_t buzzerPin = 18;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

int buttonState = LOW;
int lastButtonReading = LOW;

// Beep en el zumbador (compatible con core 2.x y 3.x)
void beep(int freq, int ms) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWriteTone(buzzerPin, freq);
  delay(ms);
  ledcWriteTone(buzzerPin, 0);
#else
  ledcWriteTone(0, freq);
  delay(ms);
  ledcWriteTone(0, 0);
#endif
}

void setup() {
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(outputPin, LOW);

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(buzzerPin, 2000, 8);
#else
  ledcSetup(0, 2000, 8);
  ledcAttachPin(buzzerPin, 0);
#endif
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        int newState = !digitalRead(outputPin);
        digitalWrite(outputPin, newState);

        beep(1000, 100);  // ADICIONAL: beep de confirmación
      }
    }
  }

  lastButtonReading = reading;
}