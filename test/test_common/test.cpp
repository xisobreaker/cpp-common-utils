#include "test.h"

#include "xiso_assert.h"
#include "xiso_exception.h"
#include "xiso_hardware.h"
#include "xiso_string.h"
#include "xiso_system.h"
#include "xiso_timer.h"

#include <chrono>
#include <exception>
#include <iostream>

void test_hardware_all()
{
    // 获取网卡名称
    std::vector<std::string> vecNames;
    if (xiso::get_network_names(vecNames)) {
        for (auto name : vecNames) {
            std::string macAddress;
            if (xiso::get_mac_address(macAddress, name)) {
                std::cout << "1. mac address: " << macAddress << " - " << name << std::endl;
            }
        }
    }

    std::map<std::string, std::string> macAddressMap;
    if (xiso::get_all_mac_address(macAddressMap)) {
        for (auto macPair : macAddressMap) {
            std::cout << "2. mac address: " << macPair.second << " - " << macPair.first << std::endl;
        }
    }

    std::string cpuId;
    xiso::get_cpu_id(cpuId);
    std::cout << "cpu id: " << cpuId << std::endl;
}

void test_system_all()
{
    std::string command = "lsblk -nls|egrep 'disk|part'";
    std::string result;
    if (execute_shell_command(result, command)) {
        std::cout << "result: " << result << std::endl;
    }
}

void test_str_split()
{
    std::string message = ";RTP/AVP;multicast;;ttl=127;";
    auto        vecStrs = xiso::str_split(message, ";");

    xiso_assert_strequal(vecStrs[0].c_str(), "RTP/AVP");
    xiso_assert_strequal(vecStrs[1].c_str(), "multicast");
    xiso_assert_strequal(vecStrs[2].c_str(), "ttl=127");
}

void test_hex_string()
{
    std::string   str          = "01 00 5E 00 01 8C";
    unsigned char buffer[1024] = {0};

    int len = xiso::hexstr2bytes(buffer, 1024, str.c_str(), str.length());
    xiso_assert_equal(buffer[0], 0x01);
    xiso_assert_equal(buffer[1], 0x00);
    xiso_assert_equal(buffer[2], 0x5E);
    xiso_assert_equal(buffer[3], 0x00);
    xiso_assert_equal(buffer[4], 0x01);
    xiso_assert_equal(buffer[5], 0x8C);

    std::string packet = xiso::bytes2hexstr(buffer, len);
    xiso_assert_strequal(str.c_str(), packet.c_str());
}

void test_str_format()
{
    std::string world = "World";
    std::string msg   = xiso::str_format("Hello, %s", world.c_str());
    xiso_assert_strequal("Hello, World", msg.c_str());
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

    char *str = xiso::str_split_values(message, ' ', "sllsss", &username, &sess_id, &sess_version, &nettype, &addrtype, &addr);
    xiso_assert_strequal(username, "-");
    xiso_assert_equal(sess_id, 2256153820);
    xiso_assert_equal(sess_version, 2256453820);
    xiso_assert_strequal(nettype, "IN");
    xiso_assert_strequal(addrtype, "IP4");
    xiso_assert_strequal(addr, "0.0.0.0");
}

void test_timer()
{
    std::chrono::seconds      sec(1717861911);
    std::chrono::milliseconds msec(1717861911100);
    std::chrono::microseconds usec(1717861911100664);

    std::string datetime = "";

    datetime = xiso::timepoint_format(xiso::timestamp_to_timepoint(sec));
    xiso_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.000000");

    datetime = xiso::timepoint_format(xiso::timestamp_to_timepoint(msec));
    xiso_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100000");

    datetime = xiso::timepoint_format(xiso::timestamp_to_timepoint(usec));
    xiso_assert_strequal(datetime.c_str(), "2024-06-08 23:51:51.100664");

    uint64_t microsec = xiso::string_format_time("YYYY-MM-DD HH:mm:ss.SSSSSS", datetime);
    xiso_assert_equal(microsec, 1717861911100664);
}

void test_exception()
{
    try {
        throw xiso::XisoException("hello, world!");
    } catch (const std::exception &e) {
        std::cout << "length: " << strlen(e.what()) << ", error: " << e.what() << std::endl;
    }

    try {
        int         value = 999;
        std::string msg   = "world!";
        const char  buf[] = "akakakak";
        std::string msg2  = "world2222";
        throw xiso::XisoException("hello %d %s %lf %s %s %d %s", 11234, msg, 123.123, buf, "isastring", value, std::move(msg2));
    } catch (const std::exception &e) {
        std::cout << "length: " << strlen(e.what()) << ", error: " << e.what() << std::endl;
    }
}

struct testcase_t main_testcases[] = {{test_hardware_all},
                                      {test_system_all},
                                      {test_str_split},
                                      {test_hex_string},
                                      {test_str_format},
                                      {test_str_split_values},
                                      {test_timer},
                                      {test_exception},
                                      END_OF_TESTCASES};