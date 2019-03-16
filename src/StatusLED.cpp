#include "StatusLED.h"

#include <Arduino.h>

namespace EasyESP {
    StatusLED::StatusLED() {}

    void handleFlashLED() {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    void StatusLED::setupLEDStart() {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
        _flasher.attach(0.5, &handleFlashLED);
    }

    void StatusLED::setupLEDStop() {
        _flasher.detach();
        digitalWrite(LED_BUILTIN, HIGH);
    }

    void StatusLED::signalError(uint8_t flashCount) {
        uint8_t counter = 0;
        while(counter++ < flashCount) {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            delay(100);
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            delay(100);
        }
    }
}