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
  

/**
 * @brief Get the network names object
 *
 * @param outVec
 * @return true
 * @return false
 */
bool get_network_names(std::vector<std::string> &outVec);

/**
 * @brief Get the mac address object
 *
 * @param macAddress
 * @param netname
 * @return true
 * @return false
 */
bool get_mac_address(std::string &macAddress, const std::string &netname);

/**
 * @brief Get the all mac address object
 *
 * @param outMap
 * @return true
 * @return false
 */
bool get_all_mac_address(std::map<std::string, std::string> &outMap);

} // namespace kgr