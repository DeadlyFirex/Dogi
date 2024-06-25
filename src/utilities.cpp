#include "utilities.h"

void utl::blink(uint8_t pin, uint16_t amount, uint16_t duration) {
    pinMode(pin, OUTPUT);
    for (int i = 0; i < amount; i++) {
        digitalWrite(pin, HIGH);
        delay(duration);
        digitalWrite(pin, LOW);
        delay(duration);
    }
}

bool utl::sanitize(SerialUSB & serial, char * buffer, size_t size) {
    if (serial.available() > 0) {
        size_t len = serial.readBytesUntil('\n', buffer, size - 1);
        buffer[len] = '\0';
        return true;
    }
    return false;
}

void utl::soft_error(SerialUSB & serial, const char * message) {
    serial.printf("Error: %s\n", message);
}

[[noreturn]] void utl::error(SerialUSB & serial, const char * message) {
    serial.printf("Error: %s\n", message);

    pinMode(LED_BUILTIN, OUTPUT);
    blink(LED_BUILTIN, 5);

    rp2040.rebootToBootloader();

    while (true) {
        delay(100);
    }
}
