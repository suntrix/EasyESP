#ifndef _EASYESP_DEFAULTS_H
#define _EASYESP_DEFAULTS_H

#ifndef EASYESP_SERIAL_BAUD
#define EASYESP_SERIAL_BAUD 76800
#endif

#ifndef EASYESP_SERIAL_TIMEOUT
#define EASYESP_SERIAL_TIMEOUT 1e3            // 1 second
#endif

#ifndef EASYESP_STATUS_LED_FLASH_ENABLED
#define EASYESP_STATUS_LED_FLASH_ENABLED 0
#endif

#ifndef EASYESP_WATCHDOG_SETUP_TIMEOUT
#define EASYESP_WATCHDOG_SETUP_TIMEOUT 10e3   // 10 seconds
#endif

#ifndef EASYESP_WATCHDOG_LOOP_TIMEOUT
#define EASYESP_WATCHDOG_LOOP_TIMEOUT 10e3    // 10 seconds
#endif

#ifndef EASYESP_WATCHDOG_DEEP_SLEEP
#define EASYESP_WATCHDOG_DEEP_SLEEP 60e3    // 60 seconds
#endif

#ifndef EASYESP_WIFI_TIMEOUT
#define EASYESP_WIFI_TIMEOUT 10e3            // 10 seconds
#endif

#endif // _EASYESP_DEFAULTS_H