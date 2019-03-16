#ifndef _EASYESP_FRAMEWORK_H
#define _EASYESP_FRAMEWORK_H

#include "defaults.h"

#include <ESP8266WiFi.h>

#include "StatusLED.h"
#include "Watchdog.h"

namespace EasyESP {

    struct Config {
        const char* ssid;
        const char* password;
        const char* otaHttpsUrl;
        const char* otaHttpsFingerPrint;
        const char* otaHttpUrl;
        const char* versionName;
    };

    class Framework {

    public:
        Framework(Config config);

        typedef void (*callback_t)(Watchdog *watchdog, StatusLED *statusLED);

        void setup(callback_t callback);

        void loop(callback_t callback);

        void printDeviceInfo();

        bool connectToWifi();

        void checkForUpdates(bool useHttps = true);

        void deepSleep(uint64_t sleepTime);

        void scanPorts();

        void signalError(uint8_t error);

    private:
        Config _config;

        StatusLED _statusLED;
        Watchdog _watchdog;

        void _checkIfExistI2C();
    };
}

#endif // _EASYESP_FRAMEWORK_H