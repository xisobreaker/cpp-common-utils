// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_timer.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:41
//  描    述:
// =====================================================================================

#pragma once

#include <cassert>
#include <chrono>
#include <string>

namespace kgr {
    template <typename>
    constexpr bool dependent_false = false;

    /**
     * @brief 获取当前系统时间戳
     *
     * @tparam T
     * @return uint64_t
     */
    template <typename T>
    inline uint64_t get_current_timestamp()
    {
        static_assert(dependent_false<T>, "Template types not allowed.");
        return 0;
    }

    template <>
    inline uint64_t get_current_timestamp<std::chrono::seconds>()
    {
        auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::seconds>(tp).count();
    }

    template <>
    inline uint64_t get_current_timestamp<std::chrono::milliseconds>()
    {
        auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(tp).count();
    }

    template <>
    inline uint64_t get_current_timestamp<std::chrono::microseconds>()
    {
        auto tp = std::chrono::high_resolution_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(tp).count();
    }

    /**
     * @brief 时间戳时间转 timepoint
     *
     * @tparam T
     * @param timestamp
     * @return std::chrono::system_clock::time_point
     */
    template <typename T>
    inline std::chrono::system_clock::time_point timestamp_to_timepoint(T timestamp)
    {
        static_assert(dependent_false<T>, "Template types not allowed.");
        return std::chrono::system_clock::time_point();
    }

    template <>
    inline std::chrono::system_clock::time_point timestamp_to_timepoint(std::chrono::seconds timestamp)
    {
        return std::chrono::system_clock::time_point() + timestamp;
    }

    template <>
    inline std::chrono::system_clock::time_point timestamp_to_timepoint(std::chrono::milliseconds timestamp)
    {
        return std::chrono::system_clock::time_point() + timestamp;
    }

    template <>
    inline std::chrono::system_clock::time_point timestamp_to_timepoint(std::chrono::microseconds timestamp)
    {
        return std::chrono::system_clock::time_point() + timestamp;
    }

    /**
     * time_t 类型转 time_point
     * @param timestamp 秒时间戳
     */
    std::chrono::system_clock::time_point timer_to_timepoint(std::time_t timestamp);

    /**
     * 获取当前格式化后的时间戳
     * @return YYYY-MM-DD HH:mm:ss.SSSSSS
     */
    std::string timepoint_format(std::chrono::system_clock::time_point tp);

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
     * @brief 计算表达式耗时
     *
     * @tparam F
     * @param func lambda 表达式
     * @return double 毫秒耗时
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