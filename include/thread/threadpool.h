// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  threadpool.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:06:33
//  描    述:
// =====================================================================================

#pragma once

#include "sync_queue.h"
#include "threadtask.h"

#include <thread>

namespace xiso {
namespace thread {

class ThreadPool
{
public:
    ThreadPool(int threadNum, int taskSize = 65535);
    virtual ~ThreadPool();

private:
    void threadMain();

public:
    void     start();
    void     stop();
    bool     addTask(std::shared_ptr<IThreadTask> task);
    uint16_t taskSize()
    {
        return m_taskQueue.size();
    }

private:
    std::thread                                             *m_threads;     // 线程队列
    int                                                      m_threadNum;   // 线程池大小
    int                                                      m_maxTaskSize; // 任务队列大小
    bool                                                     m_runFlags;    // 运行标识
    xiso::container::SyncQueue<std::shared_ptr<IThreadTask>> m_taskQueue;   // 任务队列
};

} // namespace thread
} // namespace xiso