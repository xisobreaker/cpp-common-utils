#include "kgr_string.h"

#include <cassert>

#define EXPECT_EQ(a, b) (assert(a == b))

void test_string()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::string_split(message, ";");

    EXPECT_EQ(vecStrs[0], "RTP/AVP");
    EXPECT_EQ(vecStrs[1], "multicast");
    EXPECT_EQ(vecStrs[2], "ttl=127");
}

void test_hex_string()
{
    std::string   str          = "01005e00018c";
    unsigned char buffer[1024] = {0};

    int len = kgr::hexstring2bytes(buffer, 1024, str.c_str(), str.length());
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x00);
    EXPECT_EQ(buffer[2], 0x5E);
    EXPECT_EQ(buffer[3], 0x00);
    EXPECT_EQ(buffer[4], 0x01);
    EXPECT_EQ(buffer[5], 0x8C);
}

int main(int argc, char *argv[])
{
    test_string();
    test_hex_string();
    return 0;
}
