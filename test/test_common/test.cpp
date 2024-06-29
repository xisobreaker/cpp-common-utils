#include "test.h"

#include "kgr_assert.h"
#include "kgr_string.h"
#include "kgr_timer.h"

#include <chrono>

void test_string_split()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::string_split(message, ";");

    kgr_assert_strequal(vecStrs[0].c_str(), "RTP/AVP");
    kgr_assert_strequal(vecStrs[1].c_str(), "multicast");
    kgr_assert_strequal(vecStrs[2].c_str(), "ttl=127");
}

void test_hex_string()
{
    std::string   str          = "01 00 5E 00 01 8C";
    unsigned char buffer[1024] = {0};

    int len = kgr::hexstr2bytes(buffer, 1024, str.c_str(), str.length());
    kgr_assert_equal(buffer[0], 0x01);
    kgr_assert_equal(buffer[1], 0x00);
    kgr_assert_equal(buffer[2], 0x5E);
    kgr_assert_equal(buffer[3], 0x00);
    kgr_assert_equal(buffer[4], 0x01);
    kgr_assert_equal(buffer[5], 0x8C);

    std::string packet = kgr::bytes2hexstr(buffer, len);
    kgr_assert_strequal(str.c_str(), packet.c_str());
}

void test_timer()
{
    std::chrono::seconds      sec(1717861911);
    std::chrono::milliseconds msec(1717861911100);
    std::chrono::microseconds usec(1717861911100664);

    std::string datetime = "";

    datetime = kgr::get_format_datetime(kgr::timestamp_to_timepoint(sec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.000000");
    datetime = kgr::get_format_datetime(kgr::timestamp_to_timepoint(msec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100000");
    datetime = kgr::get_format_datetime(kgr::timestamp_to_timepoint(usec));
    kgr_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100664");
}
