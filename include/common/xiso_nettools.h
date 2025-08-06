// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  xiso_nettools.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-09-06 13:18:43
//  描    述:
// =====================================================================================

#pragma once

#include <arpa/inet.h>
#include <cassert>
#include <stdexcept>
#include <type_traits>

namespace xiso {

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

const struct sockaddr     *sockaddr_cast(const struct sockaddr_in *addr);
const struct sockaddr     *sockaddr_cast(const struct sockaddr_in6 *addr);
struct sockaddr           *sockaddr_cast(struct sockaddr_in6 *addr);
const struct sockaddr_in  *sockaddr_in_cast(const struct sockaddr *addr);
const struct sockaddr_in6 *sockaddr_in6_cast(const struct sockaddr *addr);

/**
 * @brief
 *
 * @param buf
 * @param size
 * @param addr
 */
void sockaddr_to_ip(char *buf, size_t size, const struct sockaddr *addr);

/**
 * @brief
 *
 * @param buf
 * @param size
 * @param addr
 */
void sockaddr_to_ipport(char *buf, size_t size, const struct sockaddr *addr);

template <typename T>
int serialize_numeric(unsigned char *buf, int index, T t)
{
    if (!std::is_arithmetic<T>::value)
        throw std::runtime_error("Not support type.");

    *(reinterpret_cast<T *>(buf + index)) = t;
    return sizeof(T);
}

template <typename T>
T deserialize_numeric(unsigned char *buf, int index)
{
    if (!std::is_arithmetic<T>::value)
        throw std::runtime_error("Not support type.");

    return *(reinterpret_cast<T *>(buf + index));
}

} // namespace xiso