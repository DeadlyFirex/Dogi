#pragma once

#include <Arduino.h>
#include <time.h>

#include <string>
#include <list>
#include <map>
#include <functional>

#define MAX_MESSAGE 1024
#define MAX_SIZE 64

namespace cmd {
    extern char current_message[MAX_MESSAGE];
    extern std::list<uint16_t> command_list[MAX_SIZE];

    bool process(const char * message);
    void help();
    void time();
    void date();
    void raw_time();
    void internal();
    void last();
    void pause();
    void resume();
    void readout();
}