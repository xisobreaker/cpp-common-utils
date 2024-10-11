// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  logging.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:06:25
//  描    述:
// =====================================================================================

#pragma once

#include "log_manager.h"
#include "xiso_file.h"
#include "xiso_timer.h"

#include <cstring>
#include <string>

#if defined(__GNUC__)
    #define log_debug(format, args...)                                                                                     \
        do {                                                                                                               \
            xiso::log::LogManager *logManager = xiso::log::LogManager::getInstance();                                      \
            std::string            datetime   = xiso::get_current_format_datetime();                                       \
            const char            *basename   = xiso::extract_file_name(__FILE__);                                         \
            logManager->logRecord(                                                                                         \
                xiso::log::LOG_LEVEL_DEBUG, "[%s][%s:%d][D]: " format "\n", datetime.c_str(), basename, __LINE__, ##args); \
        } while (0)

    #define log_info(format, args...)                                                                                     \
        do {                                                                                                              \
            xiso::log::LogManager *logManager = xiso::log::LogManager::getInstance();                                     \
            std::string            datetime   = xiso::get_current_format_datetime();                                      \
            const char            *basename   = xiso::extract_file_name(__FILE__);                                        \
            logManager->logRecord(                                                                                        \
                xiso::log::LOG_LEVEL_INFO, "[%s][%s:%d][I]: " format "\n", datetime.c_str(), basename, __LINE__, ##args); \
        } while (0)

    #define log_warn(format, args...)                                                                                     \
        do {                                                                                                              \
            xiso::log::LogManager *logManager = xiso::log::LogManager::getInstance();                                     \
            std::string            datetime   = xiso::get_current_format_datetime();                                      \
            const char            *basename   = xiso::extract_file_name(__FILE__);                                        \
            logManager->logRecord(                                                                                        \
                xiso::log::LOG_LEVEL_WARN, "[%s][%s:%d][W]: " format "\n", datetime.c_str(), basename, __LINE__, ##args); \
        } while (0)

    #define log_error(format, args...)                                                                                     \
        do {                                                                                                               \
            xiso::log::LogManager *logManager = xiso::log::LogManager::getInstance();                                      \
            std::string            datetime   = xiso::get_current_format_datetime();                                       \
            const char            *basename   = xiso::extract_file_name(__FILE__);                                         \
            logManager->logRecord(                                                                                         \
                xiso::log::LOG_LEVEL_ERROR, "[%s][%s:%d][E]: " format "\n", datetime.c_str(), basename, __LINE__, ##args); \
        } while (0)
#elif defined(_MSC_VER)
#endif

namespace xiso {
namespace log {

/**
 * 初始化全局 logManager
 * @param filename 文件名称
 * @param keepDays 日志留存时间
 * @return true/false
 */
bool init_log_manager(std::string filename, int keepDays = 30, int level = 1);

} // namespace log
} // namespace xiso