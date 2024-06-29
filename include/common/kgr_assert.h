// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_assert.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-06-11 16:34:22
//  描    述:
// =====================================================================================

#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

#define kgr_assert_equal(a, b)                                                                         \
    do {                                                                                               \
        if ((a) != (b)) {                                                                              \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)

#define kgr_assert_strequal(a, b)                                                                      \
    do {                                                                                               \
        if (std::strcmp(a, b) != 0) {                                                                  \
            std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]: " << a << " != " << b << std::endl; \
            std::abort();                                                                              \
        }                                                                                              \
    } while (false)
