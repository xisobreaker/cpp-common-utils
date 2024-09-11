// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_hardware.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-08-06 09:13:08
//  描    述:
// =====================================================================================
#pragma once

#include <map>
#include <string>
#include <vector>

namespace kgr {

struct CPUVendorID {
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;

    std::string toString() const
    {
        return std::string(reinterpret_cast<const char *>(this), 12);
    }
};

/**
 * @brief 获取网卡名称
 *
 * @param outVec
 * @return true
 * @return false
 */
bool get_network_names(std::vector<std::string> &outVec);

/**
 * @brief 获取网卡 mac 地址
 *
 * @param macAddress
 * @param netname
 * @return true
 * @return false
 */
bool get_mac_address(std::string &macAddress, const std::string &netname);

/**
 * @brief 获取所有 mac 地址
 *
 * @param outMap
 * @return true
 * @return false
 */
bool get_all_mac_address(std::map<std::string, std::string> &outMap);

/**
 * @brief 获取CPU ID
 *
 * @param cpu_id
 * @return true
 * @return false
 */
bool get_cpu_id(std::string &cpu_id);

} // namespace kgr