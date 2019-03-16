#include "Watchdog.h"

#include <ESP8266WiFi.h>

namespace EasyESP {
    Watchdog::Watchdog() {}

    void _handleTimeout() {
        Serial.println("Watchdog timeout...");

        #ifdef EASYESP_WATCHDOG_DEEP_SLEEP
            deepSleep(EASYESP_WATCHDOG_DEEP_SLEEP);
        #else
            delay(1000);
            ESP.restart();
        #endif
    }

    void Watchdog::startGuarding(uint64_t guardTime) {
        _watchdog.once(guardTime, &_handleTimeout);
        _isGuarding = true;
    }

    bool Watchdog::isGuarding() {
        return _isGuarding;
    }

    void Watchdog::finishGuarding() {
        _watchdog.detach();
        _isGuarding = false;
    }

    void Watchdog::_deepSleep(uint64_t sleepTime) {
        finishGuarding();

        char output[50];
        sprintf(output, "Going into deep sleep for %.4f seconds", sleepTime / 1e6);

        Serial.println();
        Serial.print(output);

        ESP.deepSleep(sleepTime);
        while(true){};
    }
}