#include "test.h"

#include "properties.h"
#include "xiso_assert.h"

#include <iostream>

void test_property_write()
{
    xiso::config::PropertyTree propertyTree;
    propertyTree.set("server", "ip", "192.168.1.100");
    propertyTree.set("server", "port", 10086);
    propertyTree.set("database", "ip", "127.0.0.1");
    propertyTree.set("database", "port", 3306);
    propertyTree.set("database", "username", "root");
    propertyTree.set("database", "password", "12345678");
    xiso::config::write_profile("config.ini", propertyTree);
}

void test_property_read()
{
    xiso::config::PropertyTree propertyTree;
    xiso::config::read_profile("config.ini", propertyTree);

    std::string serverIp     = propertyTree.get("server", "ip").asString();
    uint16_t    serverPort   = propertyTree.get("server", "port").asUInt();
    std::string databaseIp   = propertyTree.get("database", "ip").asString();
    uint16_t    databasePort = propertyTree.get("database", "port").asUInt();
    std::string databaseUser = propertyTree.get("database", "username").asString();
    std::string databasePwd  = propertyTree.get("database", "password").asString();

    xiso_assert_strequal(serverIp.c_str(), "192.168.1.100");
    xiso_assert_equal(serverPort, 10086);
    xiso_assert_strequal(databaseIp.c_str(), "127.0.0.1");
    xiso_assert_equal(databasePort, 3306);
    xiso_assert_strequal(databaseUser.c_str(), "root");
    xiso_assert_strequal(databasePwd.c_str(), "12345678");
}

struct testcase_t main_testcases[] = {{test_property_write}, {test_property_read}, END_OF_TESTCASES};