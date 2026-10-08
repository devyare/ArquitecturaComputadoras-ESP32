#include <Arduino.h>

constexpr uint8_t PWM_PIN = 2;
constexpr uint8_t PWM_PIN2 = 4;          //  segundo LED
constexpr uint8_t PWM_CHANNEL = 0;
constexpr uint8_t PWM_CHANNEL2 = 1;      // segundo canal PWM
constexpr uint16_t PWM_FREQUENCY = 500;
constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint16_t PWM_MAX = (1 << PWM_RESOLUTION) - 1;
constexpr uint16_t PWM_STEP_DELAY_MS = 10;

void setup() {
    pinMode(PWM_PIN, OUTPUT);
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(PWM_PIN, PWM_CHANNEL);

    pinMode(PWM_PIN2, OUTPUT);                                  
    ledcSetup(PWM_CHANNEL2, PWM_FREQUENCY, PWM_RESOLUTION);     
    ledcAttachPin(PWM_PIN2, PWM_CHANNEL2);                      

    Serial.begin(115200);
}

void loop() {
    for (uint16_t dutyCycle = 0; dutyCycle <= PWM_MAX; ++dutyCycle) {
        ledcWrite(PWM_CHANNEL, dutyCycle);
        ledcWrite(PWM_CHANNEL2, PWM_MAX - dutyCycle);  
        delay(PWM_STEP_DELAY_MS);
        Serial.println(dutyCycle);
    }

    for (int16_t dutyCycle = PWM_MAX - 1; dutyCycle >= 0; --dutyCycle) {
        ledcWrite(PWM_CHANNEL, dutyCycle);
        ledcWrite(PWM_CHANNEL2, PWM_MAX - dutyCycle);  
        delay(PWM_STEP_DELAY_MS);
        Serial.println(dutyCycle);
    }
}