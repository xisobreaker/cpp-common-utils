// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  xiso_system.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:34
//  描    述:
// =====================================================================================

#pragma once

#include "config/platform.h"

#include <string>

#if defined(XISO_PLATFORM_LINUX)

/**
 * @brief UNIX 信号处理
 *
 * @param signo 系统信号
 * @param handler 信号处理回调
 */
void sig_process(int signo, void (*handler)(int));

/**
 * @brief 执行shell命令
 *
 * @param result
 * @param command
 * @return true
 * @return false
 */
bool execute_shell_command(std::string &result, const std::string &command);

#endif
