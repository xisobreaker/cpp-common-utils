#include "xiso_timezone.h"

DateTime::DateTime()
{
}

DateTime::DateTime(const struct tm &t) :
    year(t.tm_year + 1900), month(t.tm_mon + 1), day(t.tm_mday), hour(t.tm_hour), minute(t.tm_min), second(t.tm_sec)
{
}

DateTime::DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second) :
    year(_year), month(_month), day(_day), hour(_hour), minute(_minute), second(_second)
{
}

std::string DateTime::toIsoString() const
{
    char buf[64];
    snprintf(buf, sizeof buf, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
    return buf;
}
