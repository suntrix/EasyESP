#ifndef _EasyESP_STATUS_LED_H
#define _EasyESP_STATUS_LED_H

#include <Ticker.h>

namespace EasyESP {
    class StatusLED {

    public:
        StatusLED();

        void setupLEDStart();
        void setupLEDStop();

        void signalError(uint8_t flashCount);

    private:
        Ticker _flasher;
    };
}

#endif // _EasyESP_STATUS_LED_H