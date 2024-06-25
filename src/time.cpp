#include "time.h"

struct time::_cmp_str {
    bool operator()(const char * a, const char * b) const {
        return std::strcmp(a, b) < 0;
    }
};

std::map<const char *, int, time::_cmp_str> time::_month_map = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
    {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
    {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

short time::parse_month(const char * month) {
    auto it = time::_month_map.find(month);

    if (it != _month_map.end()) {
        return it->second;
    }
    return 0;
}

time::_time_struct time::parse(const char * date_str, const char * time_str) {
    time::_time_struct t;

    char date[] = __DATE__;
    char month[4];
    int day, year;

    sscanf(date, "%s %d %d", month, &day, &year);

    t.mnth = parse_month(month);
    t.dy = day;
    t.yr = year;

    char timeStr[] = __TIME__;
    int hr, min, sec;

    sscanf(timeStr, "%d:%d:%d", &hr, &min, &sec);

    t.hr = hr;
    t.min = min;
    t.sec = sec;

    return t;
}

void time::sync() {
    time::_time_struct t = time::parse(__DATE__, __TIME__);
    setTime(t.hr, t.min, t.sec, t.dy, t.mnth, t.yr);
}

time_t time::get() {
    return now();
}
