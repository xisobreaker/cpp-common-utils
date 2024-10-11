// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  scheduled.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-09-19 19:01:20
//  描    述:  定时任务处理类
// =====================================================================================
#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <set>
#include <thread>

namespace xiso {

class Scheduled
{
    typedef std::function<void()>     ScheduledFunc;
    typedef std::chrono::system_clock SystemClock;

    struct CrontabTask {
        std::function<void()>                              callback;
        std::chrono::time_point<std::chrono::system_clock> nextTime;
        std::chrono::microseconds                          period;

        bool operator<(const CrontabTask &task) const
        {
            return this->nextTime < task.nextTime;
        }
    };

public:
    Scheduled();
    ~Scheduled();

private:
    void run();

public:
    /**
     * @brief 添加一次性任务
     *
     * @param fn 任务回调
     * @param tp 开始时间
     */
    void addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp);

    /**
     * @brief 添加定时周期任务
     *
     * @param fn 任务回调
     * @param tp 开始时间
     * @param period 任务周期
     */
    void addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp, const std::chrono::microseconds &period);

    /**
     * @brief 添加周期任务
     *
     * @tparam Rep
     * @tparam Period
     * @param fn 任务回调
     * @param period 任务周期
     * @param start_now 立即执行任务
     */
    template <typename Rep, typename Period>
    void addTask(ScheduledFunc &&fn, const std::chrono::duration<Rep, Period> &period, bool start_now = false)
    {
        if (start_now) {
            addTask(std::move(fn), SystemClock::now(), period);
        } else {
            addTask(std::move(fn), SystemClock::now() + period, period);
        }
    }

private:
    bool                         m_runningFlag;
    std::mutex                   m_mutexLock;
    std::condition_variable      m_condition;
    std::unique_ptr<std::thread> m_threadPtr;
    std::multiset<CrontabTask>   m_taskList;
};

} // namespace xiso