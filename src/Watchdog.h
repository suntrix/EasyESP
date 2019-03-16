#ifndef _EasyESP_WATCHDOG_H
#define _EasyESP_WATCHDOG_H

#include <Ticker.h>

namespace EasyESP {
    class Watchdog {

    public:
        Watchdog();

        void startGuarding(uint64_t guardTime);

        bool isGuarding();

        void finishGuarding();

    private:
        Ticker _watchdog;

        bool _isGuarding;

        void _deepSleep(uint64_t sleepTime);
    };
}

#endif // _EasyESP_WATCHDOG_H