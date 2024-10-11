// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  log_queue.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:06:16
//  描    述:
// =====================================================================================

#pragma once

#include "log_message.h"

#include <condition_variable>
#include <deque>
#include <mutex>

namespace xiso {
namespace log {

class LogQueue
{
public:
    LogQueue();
    virtual ~LogQueue();

public:
    LogMessage *getConsumer(uint32_t waitMs);
    void        putConsumer(LogMessage *logMessage);
    LogMessage *getProducer();
    void        putProducer(LogMessage *logMessage);
    size_t      getConsumerSize();
    size_t      getProducerSize();

private:
    std::deque<LogMessage *> m_producerQueue;
    std::deque<LogMessage *> m_consumerQueue;
    std::mutex               m_producerLock;
    std::mutex               m_consumerLock;
    std::condition_variable  m_consumerCond;
};

} // namespace log
} // namespace xiso