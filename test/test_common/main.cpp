#include "kgr_assert.h"
#include "kgr_string.h"

#include <cassert>

void test_string()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::string_split(message, ";");

    kgr::assert_strequal(vecStrs[0].c_str(), "RTP/AVP");
    kgr::assert_strequal(vecStrs[1].c_str(), "multicast");
    kgr::assert_strequal(vecStrs[2].c_str(), "ttl=127");
}

void test_hex_string()
{
    std::string   str          = "01005e00018c";
    unsigned char buffer[1024] = {0};

    int len = kgr::hexstring2bytes(buffer, 1024, str.c_str(), str.length());

    kgr::assert_equal(buffer[0], (unsigned char)0x01);
    kgr::assert_equal(buffer[1], (unsigned char)0x00);
    kgr::assert_equal(buffer[2], (unsigned char)0x5E);
    kgr::assert_equal(buffer[3], (unsigned char)0x00);
    kgr::assert_equal(buffer[4], (unsigned char)0x01);
    kgr::assert_equal(buffer[5], (unsigned char)0x8C);
}

int main(int argc, char *argv[])
{
    test_string();
    test_hex_string();
    return 0;
}
