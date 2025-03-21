// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  platform.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:22
//  描    述:
// =====================================================================================

#ifndef _PLATFORM_H_H_H
#define _PLATFORM_H_H_H

#if defined(XISO_PLATFORM_LINUX) || (defined(__linux) || defined(__linux__))
    #undef XISO_PLATFORM_LINUX
    #define XISO_PLATFORM_LINUX 1

    #define XISO_PLATFORM_NAME "Linux"

#elif defined(XISO_PLATFORM_WINDOWS) || (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64))
    #undef XISO_PLATFORM_WINDOWS
    #define XISO_PLATFORM_WINDOWS 1

    #define XISO_PLATFORM_NAME "Windows"
#endif

#endif
