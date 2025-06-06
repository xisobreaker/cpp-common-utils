#include "xiso_hardware.h"

#include <cpuid.h>
#include <dirent.h>
#include <fstream>
#include <ifaddrs.h>
#include <iostream>

namespace xiso {

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

bool get_cpu_id(std::string &cpu_id)
{
    unsigned int level = 0;
    unsigned int eax   = 0;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;

    __get_cpuid(level, &eax, &ebx, &ecx, &edx);
    CPUVendorID vendorID{.ebx = ebx, .edx = edx, .ecx = ecx};

    static const std::map<std::string, std::string> vendorIdToName = {
        {"GenuineIntel", "Intel"                 },
        {"AuthenticAMD", "AMD"                   },
        {"CyrixInstead", "Cyrix"                 },
        {"CentaurHauls", "Centaur"               },
        {"SiS SiS SiS ", "SiS"                   },
        {"NexGenDriven", "NexGen"                },
        {"GenuineTMx86", "Transmeta"             },
        {"RiseRiseRise", "Rise"                  },
        {"UMC UMC UMC ", "UMC"                   },
        {"Geode by NSC", "National Semiconductor"},
    };

    cpu_id = vendorID.toString();
    return true;

    return false;
}

} // namespace xiso