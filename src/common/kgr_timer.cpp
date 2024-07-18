#include "kgr_timer.h"

#include "config/platform.h"
#include "kgr_string.h"

#include <chrono>
#include <iomanip>

namespace kgr {

std::chrono::system_clock::time_point timer_to_timepoint(std::time_t timestamp)
{
    return std::chrono::system_clock::from_time_t(timestamp);
}

std::string timepoint_format(std::chrono::system_clock::time_point tp)
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

uint64_t datetime_to_timestamp(std::string datetime)
{
    uint16_t milliseconds = 0;
    auto     pos          = datetime.find(".");
    if (pos != std::string::npos) {
        std::string ms = datetime.substr(pos + 1);
        milliseconds   = atoi(ms.c_str());
        datetime       = datetime.substr(0, pos);
    }
    if (datetime.find("T") != std::string::npos) {
        kgr::str_replace(datetime, "T", " ");
    }

    struct tm timeinfo = {0, 0, 0, 1, 0, 70};
    if (datetime.find(" ") != std::string::npos) {
        strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo);
    } else {
        if (datetime.find("-") != std::string::npos) {
            std::vector<std::string> vecString = kgr::str_split(datetime, "-");
            if (vecString.size() > 0)
                timeinfo.tm_year = std::atoi(vecString[0].c_str()) - 1900;
            if (vecString.size() > 1)
                timeinfo.tm_mon = std::atoi(vecString[1].c_str()) - 1;
            if (vecString.size() > 2)
                timeinfo.tm_mday = std::atoi(vecString[2].c_str());
        } else if (datetime.find(":") != std::string::npos) {
            std::vector<std::string> vecString = kgr::str_split(datetime, ":");
            if (vecString.size() > 0)
                timeinfo.tm_hour = std::atoi(vecString[0].c_str());
            if (vecString.size() > 1)
                timeinfo.tm_min = std::atoi(vecString[1].c_str());
            if (vecString.size() > 2)
                timeinfo.tm_sec = std::atoi(vecString[2].c_str());
        }
    }

    time_t timer = mktime(&timeinfo);
    return (uint64_t)timer * 1000 + (uint64_t)milliseconds;
}

} // namespace kgr