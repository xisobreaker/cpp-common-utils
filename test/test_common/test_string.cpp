#include "test_string.h"

#include "kgr_assert.h"
#include "kgr_string.h"

void test_str_split()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::str_split(message, ";");

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

void test_str_format()
{
    std::string world = "World";
    std::string msg   = kgr::str_format("Hello, %s", world.c_str());
    kgr_assert_strequal("Hello, World", msg.c_str());
}

void test_str_split_values()
{
    char         *username;
    long long int sess_id;
    long long int sess_version;
    char         *nettype;
    char         *addrtype;
    char         *addr;

    char message[] = "- 2256153820 2256453820 IN IP4 0.0.0.0";

    char *str = kgr::str_split_values(message, ' ', "sllsss", &username, &sess_id, &sess_version, &nettype, &addrtype, &addr);
    kgr_assert_strequal(username, "-");
    kgr_assert_equal(sess_id, 2256153820);
    kgr_assert_equal(sess_version, 2256453820);
    kgr_assert_strequal(nettype, "IN");
    kgr_assert_strequal(addrtype, "IP4");
    kgr_assert_strequal(addr, "0.0.0.0");
}

void test_string_all()
{
    test_str_split();
    test_hex_string();
    test_str_format();
    test_str_split_values();
}