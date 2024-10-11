// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  log_message.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:06:10
//  描    述:
// =====================================================================================

#pragma once

#include <cstdarg>

namespace xiso {
namespace log {

class LogMessage
{
public:
    LogMessage();
    virtual ~LogMessage();

public:
    char *getMessage();
    int   setMessage(int level, const char *format, va_list &args);
    int   length();
    int   level();

private:
    int   m_level;
    char *m_buffer;
    int   m_length;
};

} // namespace log
} // namespace xiso