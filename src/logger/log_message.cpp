#include "log_message.h"

#include "config/platform.h"
#include "log_constants.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace xiso {
namespace log {

LogMessage::LogMessage()
{
    m_length = 0;
    m_buffer = new char[LOG_LINE_SIZE];
}

LogMessage::~LogMessage()
{
    if (m_buffer) {
        delete[] m_buffer;
    }
}

char *LogMessage::getMessage()
{
    return m_buffer;
}

int LogMessage::setMessage(int level, const char *format, va_list &args)
{
#if defined(XISO_PLATFORM_LINUX)
    int n = vsnprintf(m_buffer, LOG_LINE_SIZE, format, args);
#elif defined(XISO_PLATFORM_WINDOWS)
    int n = vsprintf_s(m_buffer, LOG_LINE_SIZE, format, args);
#endif

    m_level  = level;
    m_length = strlen(m_buffer);
    return m_length;
}

int LogMessage::length()
{
    return m_length;
}

int LogMessage::level()
{
    return m_level;
}

} // namespace log
} // namespace xiso