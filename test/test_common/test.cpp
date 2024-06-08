#include "test.h"

#include "kgr_assert.h"
#include "kgr_string.h"
#include "kgr_timer.h"

#include <cstdint>
#include <iostream>

void test_string_split()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::string_split(message, ";");

    kgr::assert_strequal(vecStrs[0].c_str(), "RTP/AVP");
    kgr::assert_strequal(vecStrs[1].c_str(), "multicast");
    kgr::assert_strequal(vecStrs[2].c_str(), "ttl=127");
}

void test_hex_string()
{
    std::string   str          = "01 00 5E 00 01 8C";
    unsigned char buffer[1024] = {0};

    int len = kgr::hexstring2bytes(buffer, 1024, str.c_str(), str.length());
    kgr::assert_equal(buffer[0], (unsigned char)0x01);
    kgr::assert_equal(buffer[1], (unsigned char)0x00);
    kgr::assert_equal(buffer[2], (unsigned char)0x5E);
    kgr::assert_equal(buffer[3], (unsigned char)0x00);
    kgr::assert_equal(buffer[4], (unsigned char)0x01);
    kgr::assert_equal(buffer[5], (unsigned char)0x8C);

    std::string packet = kgr::bytes2hex_string(buffer, len);
    kgr::assert_strequal(str.c_str(), packet.c_str());
}

void test_timer()
{
    uint32_t    sec      = 1717861911;
    uint32_t    usec     = 100664;
    std::string datetime = kgr::get_format_datetime(sec, usec);
    kgr::assert_equal(datetime.c_str(), "2024-06-08 23:51:51.100664");
}