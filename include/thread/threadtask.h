// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  threadtask.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:06:40
//  描    述:
// =====================================================================================

#pragma once

#include <functional>
namespace kgr {
    namespace thread {
        class IThreadTask
        {
        public:
            IThreadTask()          = default;
            virtual ~IThreadTask() = default;

        public:
            virtual void runTask() = 0;
        };

        template <typename T>
        class ThreadTask : public IThreadTask
        {
            typedef std::function<void(T)>   TaskCallback;
            typedef std::function<void(T &)> ReleaseCallback;

        public:
            ThreadTask(TaskCallback callback, T arg)
            {
                m_callback    = callback;
                m_callbackArg = arg;
            }

            ThreadTask(TaskCallback callback, T arg, ReleaseCallback release)
            {
                ThreadTask(callback, arg);
                m_release = release;
            }

            virtual ~ThreadTask()
            {
                if (m_release)
                    m_release(m_callbackArg);
            }

        public:
            void runTask() override
            {
                if (m_callback)
                    m_callback(m_callbackArg);
            }

        private:
            TaskCallback    m_callback;
            T               m_callbackArg;
            ReleaseCallback m_release;
        };
    } // namespace thread
} // namespace kgr