// #define EASYESP_SERIAL_BAUD 76800       // this baud rate usually stops the ESP from outputting garbage right after boot
// #define EASYESP_SERIAL_TIMEOUT 1e3      // 1 second

// #define EASYESP_STATUS_LED_FLASH_ENABLED 1

// #define EASYESP_WATCHDOG_SETUP_TIMEOUT 10e3     // 10 seconds
// #define EASYESP_WATCHDOG_LOOP_TIMEOUT 10e3      // 10 seconds
// #define EASYESP_WATCHDOG_DEEP_SLEEP 60e3        // 60 seconds

// #define EASYESP_WIFI_TIMEOUT 10e3               // 10 seconds

#define SECRETS_WIFI_SSID ""
#define SECRETS_WIFI_PASSWORD ""

#define SECRETS_OTA_SERVER_HTTPS_URL "https://example.com/update"
#define SECRETS_OTA_SERVER_FINGERPRINT "4E:2C:96:B0:10:B5:26:22:8B:2D:2C:2F:70:BE:62:0A:41:6D:F8:59"
#define SECRETS_OTA_SERVER_HTTP_URL "http://example.com/update"

// #define RUNTIME_INTERVAL = 600e6

#include <Framework.h>

EasyESP::Config config = {
    .ssid = SECRETS_WIFI_SSID,
    .password = SECRETS_WIFI_PASSWORD,
    .otaHttpsUrl = SECRETS_OTA_SERVER_HTTPS_URL,
    .otaHttpsFingerPrint = SECRETS_OTA_SERVER_FINGERPRINT,
    .otaHttpUrl = SECRETS_OTA_SERVER_HTTP_URL,
    .versionName = "2.0.1"
};

EasyESP::Framework framework;

void setupCallback(EasyESP::Watchdog *watchdog, EasyESP::StatusLED *statusLED) {
    // your setup code here
}

void loopCallback(EasyESP::Watchdog *watchdog, EasyESP::StatusLED *statusLED) {
    // your loop code here
}

void setup() {
    framework.setup(&setupCallback);

    // framework.deepSleep(RUNTIME_INTERVAL - micros());
}

void loop() {
    framework.loop(&loopCallback);
}