#include "test_timer.h"

#include "kgr_assert.h"
#include "kgr_timer.h"

#include <chrono>

void test_timer()
{
    std::chrono::seconds      sec(1717861911);
    std::chrono::milliseconds msec(1717861911100);
    std::chrono::microseconds usec(1717861911100664);

    std::string datetime = "";

    datetime = kgr::timepoint_format(kgr::timestamp_to_timepoint(sec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.000000");

    datetime = kgr::timepoint_format(kgr::timestamp_to_timepoint(msec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100000");

    datetime = kgr::timepoint_format(kgr::timestamp_to_timepoint(usec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100664");

    uint64_t microsec = kgr::string_format_time("YYYY-MM-DD HH:mm:ss.SSSSSS", datetime);
    kgr_assert_equal(microsec, 1717861911100664);
}

void test_timer_all()
{
    test_timer();
}