#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace xiso {

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(std::chrono::system_clock::time_point tp);

    template <typename Rep, typename Period>
    Timestamp(std::chrono::duration<Rep, Period> ts) : timepoint_(ts)
    {
        uint64_t microsec = std::chrono::duration_cast<std::chrono::microseconds>(timepoint_.time_since_epoch()).count();
        timeval_.tv_sec   = microsec / 1000000;
        timeval_.tv_usec  = microsec % 1000000;
    };
    ~Timestamp();

public:
    static Timestamp now();

public:
    std::string toString() const;

    int64_t toSeconds()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(timepoint_.time_since_epoch()).count();
    }

    int64_t toMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint_.time_since_epoch()).count();
    }

    int64_t toMicroseconds()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(timepoint_.time_since_epoch()).count();
    }

private:
    std::chrono::system_clock::time_point timepoint_;
    struct timeval                        timeval_;
};

} // namespace xiso