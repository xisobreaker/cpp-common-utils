#include "test.h"

#include "kgr_assert.h"
#include "properties.h"

#include <iostream>

void test_property_write()
{
    kgr::config::PropertyTree propertyTree;
    propertyTree.set("server", "ip", "192.168.1.100");
    propertyTree.set("server", "port", 10086);
    propertyTree.set("database", "ip", "127.0.0.1");
    propertyTree.set("database", "port", 3306);
    propertyTree.set("database", "username", "root");
    propertyTree.set("database", "password", "12345678");
    kgr::config::write_profile("config.ini", propertyTree);
}

void test_property_read()
{
    kgr::config::PropertyTree propertyTree;
    kgr::config::read_profile("config.ini", propertyTree);

    std::string serverIp     = propertyTree.get("server", "ip").asString();
    uint16_t    serverPort   = propertyTree.get("server", "port").asUInt();
    std::string databaseIp   = propertyTree.get("database", "ip").asString();
    uint16_t    databasePort = propertyTree.get("database", "port").asUInt();
    std::string databaseUser = propertyTree.get("database", "username").asString();
    std::string databasePwd  = propertyTree.get("database", "password").asString();

    kgr_assert_strequal(serverIp.c_str(), "192.168.1.100");
    kgr_assert_equal(serverPort, 10086);
    kgr_assert_strequal(databaseIp.c_str(), "127.0.0.1");
    kgr_assert_equal(databasePort, 3306);
    kgr_assert_strequal(databaseUser.c_str(), "root");
    kgr_assert_strequal(databasePwd.c_str(), "12345678");
}

struct testcase_t main_testcases[] = {{test_property_write}, {test_property_read}, END_OF_TESTCASES};