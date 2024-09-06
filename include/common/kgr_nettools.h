// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_nettools.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-09-06 13:18:43
//  描    述:
// =====================================================================================

#pragma once

namespace kgr {

/**
 * @brief 主机序转网络序(8字节)
 *
 * @param val 主机序
 * @return unsigned long long 网络序
 */
unsigned long long htonll(unsigned long long val);

/**
 * @brief 网络序转主机序(8字节)
 *
 * @param val 网络序
 * @return unsigned long long 主机序
 */
unsigned long long ntohll(unsigned long long val);

} // namespace kgr