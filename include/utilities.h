#pragma once

#include <Arduino.h>

namespace utl {
    void blink(uint8_t pin, uint16_t amount, uint16_t delay = 300u);
    bool sanitize(SerialUSB & serial, char * buffer, size_t size);
    void soft_error(SerialUSB & serial, const char * message);
    [[noreturn]] void error(SerialUSB & serial, const char * message);
}