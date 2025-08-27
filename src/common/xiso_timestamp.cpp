#include "xiso_timestamp.h"

#include <chrono>
#include <ctime>

namespace xiso {

Timestamp::Timestamp() : timepoint_(std::chrono::microseconds::zero()), timeval_({.tv_sec = 0, .tv_usec = 0})
{
}

Timestamp::Timestamp(std::chrono::system_clock::time_point tp) : timepoint_(tp)
{
    uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(timepoint_.time_since_epoch()).count();
    timeval_.tv_sec   = microsec / 1000000;
    timeval_.tv_usec  = microsec % 1000000;
}

Timestamp::~Timestamp()
{
}

Timestamp Timestamp::now()
{
    return Timestamp(std::chrono::system_clock::now());
}

std::string Timestamp::toString() const
{
    struct tm localtm;
    localtime_r(&timeval_.tv_sec, &localtm);

    char formatter[128] = {};
    snprintf(formatter, 128, "%04d-%02d-%02d %02d:%02d:%02d.%06ld", localtm.tm_year + 1900, localtm.tm_mon + 1,
             localtm.tm_mday, localtm.tm_hour, localtm.tm_min, localtm.tm_sec, timeval_.tv_usec);
    return std::string(formatter);
}

} // namespace xiso