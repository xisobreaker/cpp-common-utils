#include "xiso_timer.h"

#include <chrono>
#include <iomanip>

namespace xiso {

std::chrono::system_clock::time_point timer_to_timepoint(std::time_t timestamp)
{
    return std::chrono::system_clock::from_time_t(timestamp);
}

std::string timepoint_format(const std::chrono::system_clock::time_point &tp)
{
    time_t timer = std::chrono::system_clock::to_time_t(tp);

    std::ostringstream oss;
    char               datetime[32] = {0};
    std::strftime(datetime, 32, "%Y-%m-%d %H:%M:%S", std::localtime(&timer));

    auto micros   = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
    auto second   = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
    auto microsec = (micros - second).count();
    oss << datetime << "." << std::setfill('0') << std::setw(6) << microsec;
    return oss.str();
}

std::string get_current_format_datetime()
{
    auto tp = std::chrono::system_clock::now();
    return timepoint_format(tp);
}

uint64_t string_format_time(const std::string &format, const std::string &datetime)
{
    auto conv_ch = [](char c) {
        return c - '0';
    };

    std::string seps           = "-:.";
    struct tm   timeinfo       = {0, 0, 0, 0, 0, 0};
    char        microsecond[7] = "000000";
    int         microIndex     = 0;

    for (int i = 0; i < format.size(); i++) {
        while (format.size() > i && seps.find(format.at(i), 0) == std::string::npos) {
            switch (format.at(i)) {
                case 'Y':
                    timeinfo.tm_year = timeinfo.tm_year * 10 + conv_ch(datetime.at(i));
                    break;
                case 'M':
                    timeinfo.tm_mon = timeinfo.tm_mon * 10 + conv_ch(datetime.at(i));
                    break;
                case 'D':
                    timeinfo.tm_mday = timeinfo.tm_mday * 10 + conv_ch(datetime.at(i));
                    break;
                case 'H':
                    timeinfo.tm_hour = timeinfo.tm_hour * 10 + conv_ch(datetime.at(i));
                    break;
                case 'm':
                    timeinfo.tm_min = timeinfo.tm_min * 10 + conv_ch(datetime.at(i));
                    break;
                case 's':
                    timeinfo.tm_sec = timeinfo.tm_sec * 10 + conv_ch(datetime.at(i));
                    break;
                case 'S':
                    if (datetime.size() > i) {
                        microsecond[microIndex++] = datetime.at(i);
                    }
                    break;
            }
            ++i;
        }
    }

    if (timeinfo.tm_year > 0)
        timeinfo.tm_year -= 1900;
    if (timeinfo.tm_mon > 0)
        timeinfo.tm_mon -= 1;

    if (timeinfo.tm_year < 70)
        timeinfo.tm_year = 70;
    if (timeinfo.tm_mday == 0)
        timeinfo.tm_mday = 1;

    time_t   timer = mktime(&timeinfo);
    uint32_t usec  = std::stoi(microsecond);
    return (uint64_t)timer * 1000000 + usec;
}

} // namespace xiso