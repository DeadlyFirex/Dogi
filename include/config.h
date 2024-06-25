#pragma once

#define VERSION "0.1.0"
#define DEBUG_SERIAL 0
#define WATCHDOG_DELAY_MS 1500u

#include <Arduino.h>

namespace cfg {
    extern bool watchdog_setup;
    extern unsigned long watchdog_c1_last_reset;

    void setup_wdt();
    void reset_wdt();
}
