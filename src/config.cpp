#include "config.h"

bool cfg::watchdog_setup = false;
unsigned long cfg::watchdog_c1_last_reset = 0u;

void cfg::setup_wdt() {
    if (rp2040.cpuid() == 1) {
        return;
    }
    cfg::watchdog_setup = true;
    rp2040.wdt_begin(WATCHDOG_DELAY_MS);
}

void cfg::reset_wdt() {
    if (rp2040.cpuid() == 1) {
        return;
    }
    rp2040.wdt_reset();
}

/*
void cfg::reset_wdt() {
    if ((millis() - cfg::watchdog_c1_last_reset) > WATCHDOG_DELAY_MS) {
        rp2040.restartCore1();
    } else if (rp2040.cpuid() == 1 && cfg::watchdog_setup) {
        cfg::watchdog_c1_last_reset = millis();
    } else if (rp2040.cpuid() == 0 && cfg::watchdog_setup) {
        rp2040.wdt_reset();
    }
}
 */
