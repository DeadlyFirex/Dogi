#pragma once

#include <Arduino.h>
#include <list>

#define RDR_PIN 20u

namespace mon {
    extern bool detected;
    extern unsigned long last_detected;
    extern char * since_message;
    extern std::list<unsigned long> detection_list;

    bool setup();
    bool check();
}