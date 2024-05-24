#include "threadpool.h"

#include <mutex>

namespace kgr {
    namespace thread {
        ThreadPool::ThreadPool(int threadNum, int taskSize) : m_threadNum(threadNum), m_maxTaskSize(taskSize), m_runFlags(false)
        {
            m_threads = new std::thread[threadNum];
        }

        ThreadPool::~ThreadPool()
        {
            if (m_threads)
                delete[] m_threads;
        }

        void ThreadPool::threadMain()
        {
            while (m_runFlags) {
                std::shared_ptr<IThreadTask> task;
                if (!m_taskQueue.pop_front(task))
                    continue;
                task->runTask();
            }
        }

        void ThreadPool::start()
        {
            m_runFlags = true;
            for (int i = 0; i < m_threadNum; i++) {
                m_threads[i] = std::thread(&ThreadPool::threadMain, this);
            }
        }

        void ThreadPool::stop()
        {
            if (!m_threads)
                return;

            m_runFlags = false;
            for (int i = 0; i < m_threadNum; i++) {
                m_taskQueue.loopbreak();
                if (m_threads[i].joinable()) {
                    m_threads[i].join();
                }
            }
        }

        bool ThreadPool::addTask(std::shared_ptr<IThreadTask> task)
        {
            if (m_taskQueue.size() >= m_maxTaskSize)
                return false;

            m_taskQueue.push_back(task);
            return true;
        }
    } // namespace thread
} // namespace kgr