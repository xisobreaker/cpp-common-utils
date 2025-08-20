#pragma once

#include <ctime>
#include <string>

struct DateTime {
    DateTime();
    explicit DateTime(const struct tm &);
    DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second);

    // "2011-12-31 12:34:56"
    std::string toIsoString() const;

    int year   = 0; // [1900, ...]
    int month  = 0; // [1, 12]
    int day    = 0; // [1, 31]
    int hour   = 0; // [0, 23]
    int minute = 0; // [0, 59]
    int second = 0; // [0, 59]
};