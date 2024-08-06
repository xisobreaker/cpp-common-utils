#include "kgr_hardware.h"

#include "config/platform.h"

#include <sstream>

#if defined(KGR_PLATFORM_LINUX)
    #include "kgr_system.h"
#endif

#include <dirent.h>
#include <fstream>
#include <ifaddrs.h>
#include <iostream>

namespace kgr {

bool get_network_names(std::vector<std::string> &outVec)
{
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *addr       = nullptr;

    int result = getifaddrs(&interfaces);
    if (result != 0) {
        std::cerr << "getifaddrs failed with error: " << result << std::endl;
        return false;
    }

    for (addr = interfaces; addr != nullptr; addr = addr->ifa_next) {
        if (addr->ifa_addr && addr->ifa_name) {
            if (addr->ifa_addr->sa_family == AF_PACKET) {
                outVec.push_back(addr->ifa_name);
            }
        }
    }
    freeifaddrs(interfaces);
    return true;
}

bool get_mac_address(std::string &macAddress, const std::string &netname)
{
    std::string addressFile;

    addressFile = "/sys/class/net/" + netname + "/address";
    std::ifstream file(addressFile);
    if (!file.is_open()) {
        return false;
    }

    std::getline(file, macAddress);
    file.close();
    return true;
}

bool get_all_mac_address(std::map<std::string, std::string> &outMap)
{
    DIR *dir = opendir("/sys/class/net/");
    if (dir == nullptr) {
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        // 读取文件内容
        std::string macAddress;
        if (!get_mac_address(macAddress, entry->d_name)) {
            continue;
        }

        outMap.insert(std::make_pair(entry->d_name, macAddress));
    }
    closedir(dir);
    return true;
}

} // namespace kgr