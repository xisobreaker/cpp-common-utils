// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  sync_queue.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:07
//  描    述:
// =====================================================================================

#pragma once

#include <atomic>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <type_traits>

namespace xiso {
namespace container {

/**
 * 线程安全的同步队列
 */
template <typename T>
class SyncQueue
{
    typedef std::deque<T> self_type;

public:
    SyncQueue() : m_shutdown(false){};
    virtual ~SyncQueue(){};

public:
    /**
     * @brief 放入队列
     *
     * @param data 入队列数据
     */
    void push_back(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push_back(data);
        m_condition.notify_one();
    }

    /**
     * @brief
     *
     * @param data
     */
    void push_back(const T &&data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push_back(std::move(data));
        m_condition.notify_one();
    }

    /**
     * @brief 出队列, 阻塞读取
     *
     * @param data
     * @return true
     * @return false
     */
    bool pop_front(T &data)
    {
        if (!m_queue.empty() && !m_shutdown) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (!m_queue.empty() && !m_shutdown) {
                data = m_queue.front();
                m_queue.pop_front();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 出队列
     *
     * @param data
     * @return true
     * @return false
     */
    bool wait_pop_front(T &data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty() && !m_shutdown) {
            m_condition.wait(lock);
        }

        if (m_queue.empty() || m_shutdown) {
            return false;
        }

        data = m_queue.front();
        m_queue.pop_front();
        return true;
    }

    /**
     * @brief 所有出队操作退出阻塞状态
     *
     */
    void shutdown()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        while (!m_queue.empty()) {
            T &data = m_queue.front();
            delete_queue_object(data);
            m_queue.pop_front();
        }
        m_shutdown = true;
        m_condition.notify_all();
    }

    /**
     * @brief 获取队列大小
     *
     * @return unsigned int
     */
    unsigned int size() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return static_cast<unsigned int>(m_queue.size());
    }

    /**
     * @brief 队列是否为空
     *
     * @return true
     * @return false
     */
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    template <typename E = T>
    typename std::enable_if<std::is_pointer<E>::value>::type delete_queue_object(T &obj)
    {
        delete obj;
    }

    template <typename E = T>
    typename std::enable_if<!std::is_pointer<E>::value>::type delete_queue_object(const E &)
    {
    }

private:
    std::atomic<bool>       m_shutdown;
    std::deque<T>           m_queue;
    mutable std::mutex      m_mutex;
    std::condition_variable m_condition;
};
} // namespace container
} // namespace xiso