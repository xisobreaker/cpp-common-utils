#include "kgr_string.h"

#define EXPECT_EQ(a, b) (a == b)

void test_string()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = kgr::string_split(message, ";");

    EXPECT_EQ(vecStrs[0], "RTP/AVP");
    EXPECT_EQ(vecStrs[1], "multicast");
    EXPECT_EQ(vecStrs[2], "ttl=127");
}

int main(int argc, char *argv[])
{
    test_string();
    return 0;
}
