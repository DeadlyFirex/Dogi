#include "monitor.h"

bool mon::detected = false;
unsigned long mon::last_detected = 0u;
char * mon::since_message = new char[16]{"?"};
std::list<unsigned long> mon::detection_list = std::list<unsigned long>();

bool mon::setup() {
    pinMode(RDR_PIN, INPUT);
    return true;
}

bool mon::check() {
    unsigned long now = millis();
    unsigned long elapsed = round((now - mon::last_detected) / 1000);

    if (digitalRead(RDR_PIN) == LOW) {
        mon::last_detected = millis();
        mon::detected = true;
        mon::detection_list.push_front(now);
    } else {
        if (elapsed > 2) {
            mon::detected = false;
        }

        auto elapsed_m = elapsed / 60;
        auto elapsed_h = elapsed_m / 60;
        
        if (elapsed_h > 0) {
            sprintf(mon::since_message, "%luh %lum ago", elapsed_h, elapsed_m % 60);
        } else if (elapsed_m > 0) {
            sprintf(mon::since_message, "%lum %lus ago", elapsed_m, elapsed % 60);
        } else {
            sprintf(mon::since_message, "%lus ago", elapsed);
        }
    }

    return mon::detected;
}