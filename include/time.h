#pragma once

#include <TimeLib.h>
#include <iostream>
#include <cstring>
#include <map>

namespace time {
    struct _cmp_str;
    struct _time_struct {
        int hr;
        int min;
        int sec;
        int dy;
        int mnth;
        int yr;
    };

    extern std::map<const char *, int, _cmp_str> _month_map;

    short parse_month(const char * month);
    time::_time_struct parse(const char * date_str, const char * time_str);
    void sync();
    time_t get();
}