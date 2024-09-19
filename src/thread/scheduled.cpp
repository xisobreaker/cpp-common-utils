#include "scheduled.h"

#include <chrono>
#include <memory>
#include <mutex>

namespace kgr {

Scheduled::Scheduled() : m_runningFlag(true)
{
    m_threadPtr.reset(new std::thread(&Scheduled::run, this));
}

Scheduled::~Scheduled()
{
    m_runningFlag = false;
    if (m_threadPtr->joinable()) {
        m_threadPtr->join();
    }
}

void Scheduled::addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp)
{
    addTask(std::move(fn), tp, std::chrono::microseconds::zero());
}

void Scheduled::addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp, const std::chrono::microseconds &period)
{
    std::lock_guard<std::mutex> guard(m_mutexLock);

    // 添加任务到有序队列
    CrontabTask task;
    task.callback = std::move(fn);
    task.nextTime = tp;
    task.period   = period;
    m_taskList.insert(std::move(task));
    m_condition.notify_one();
}

void Scheduled::run()
{
    while (m_runningFlag) {
        std::unique_lock<std::mutex> lock(m_mutexLock);
        while (m_runningFlag && m_taskList.empty()) {
            m_condition.wait(lock);
        }

        if (!m_runningFlag)
            break;

        auto task = *m_taskList.begin();
        if (SystemClock::now() >= task.nextTime) {
            m_taskList.erase(m_taskList.begin());
            lock.unlock();
            task.callback();

            // 添加下次任务
            if (task.period.count() > 0) {
                lock.lock();
                task.nextTime = task.nextTime + task.period;
                m_taskList.insert(std::move(task));
            }
        } else {
            m_condition.wait_until(lock, task.nextTime);
        }
    }
}

} // namespace kgr