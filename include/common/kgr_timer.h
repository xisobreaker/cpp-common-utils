// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_timer.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:41
//  描    述:
// =====================================================================================

#pragma once

#include <chrono>
#include <string>

namespace kgr {

    /**
     * 获取当前系统时间戳
     * @return 当前时间戳(秒)
     */
    uint64_t get_current_timestamp_seconds();

    /**
     * 获取当前系统时间戳
     * @return 当前时间戳(毫秒)
     */
    uint64_t get_current_timestamp_millis();

    /**
     * 获取当前格式化后的时间戳
     * @return YYYY-MM-DD HH:mm:ss.SSSSSS
     */
    std::string get_current_format_datetime();

    /**
     * 字符串时间转为时间戳
     * @param datetime 日期时间
     * @return 毫秒时间戳
     */
    uint64_t datetime_to_timestamp(std::string datetime);

    /**
     * time_t 转 时间字符串
     * @param timer time_t 时间戳
     * @return 日期时间
     */
    std::string timestamp_to_datetime(time_t timer);

    /**
     * 时间戳转为字符串时间
     * @param datetime 毫秒时间戳
     * @param hasMillis 是否包含毫秒时间
     * @return 日期时间
     */
    std::string milliseconds_to_datetime(uint64_t timestamp, bool hasMillis = true);

    /**
     * 计算 lambda 表达式耗时
     * @param func lambda 表达式
     * @return double 类型, 毫秒耗时
     */
    template <typename F>
    double method_elapsed_time(F const &func)
    {
        auto begin = std::chrono::system_clock::now();
        func();
        auto end = std::chrono::system_clock::now();
        return std::chrono::duration<double, std::milli>(end - begin).count();
    }

} // namespace kgr