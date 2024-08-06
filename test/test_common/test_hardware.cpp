#include "test_hardware.h"

#include "kgr_hardware.h"
#include "kgr_system.h"

#include <iostream>

void test_hardware_all()
{
    std::vector<std::string> vecNames;
    if (kgr::get_network_names(vecNames)) {
        for (auto name : vecNames) {
            std::cout << "network name: " << name << std::endl;

            std::string macAddress;
            if (kgr::get_mac_address(macAddress, name)) {
                std::cout << "mac address: " << macAddress << std::endl;
            }
        }
    }

    std::cout << "**********************************" << std::endl;
    std::map<std::string, std::string> macAddressMap;
    if (kgr::get_all_mac_address(macAddressMap)) {
        for (auto macPair : macAddressMap) {
            std::cout << "mac address: " << macPair.first << " - " << macPair.second << std::endl;
        }
    }
}

void test_system_all()
{
    std::string command = "lsblk -nls|egrep 'disk|part'";
    std::string result;
    if (execute_shell_command(result, command)) {
        std::cout << "result: " << result << std::endl;
    }
}