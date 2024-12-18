// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  xiso_assert.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-06-11 16:34:22
//  描    述:
// =====================================================================================

#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

// 比较两个对象是否相等
#define xiso_assert_equal(a, b)                                                                        \
    do {                                                                                               \
        if ((a) != (b)) {                                                                              \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

// 比较是否 a 小于 b
#define xiso_assert_lt(a, b)                                                                           \
    do {                                                                                               \
        if ((a) >= (b)) {                                                                              \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

// 比较是否 a 大于 b
#define xiso_assert_gt(a, b)                                                                           \
    do {                                                                                               \
        if ((a) <= (b)) {                                                                              \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

// 比较是否 a 小于等于 b
#define xiso_assert_le(a, b)                                                                           \
    do {                                                                                               \
        if ((a) > (b)) {                                                                               \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

// 比较是否 a 大于等于 b
#define xiso_assert_ge(a, b)                                                                           \
    do {                                                                                               \
        if ((a) < (b)) {                                                                               \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

// 比较字符串是否 a 等于 b
#define xiso_assert_strequal(a, b)                                                                     \
    do {                                                                                               \
        if (std::strcmp(a, b) != 0) {                                                                  \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)
