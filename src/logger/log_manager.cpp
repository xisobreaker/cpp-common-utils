#include "log_manager.h"

#include "log_constants.h"
#include "log_queue.h"
#include "xiso_diriterator.h"
#include "xiso_file.h"
#include "xiso_filesystem.h"
#include "xiso_string.h"
#include "xiso_timer.h"

#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace xiso {
namespace log {
LogManager *g_logManager = new LogManager();

LogManager::LogManager() : m_bRunning(false)
{
    m_bWriteLog = false;
    m_logLevel  = LOG_LEVEL_INFO;
    m_keepDays  = 0;
    m_lastTime  = 0;
    m_logQueue  = new LogQueue();
}

LogManager::~LogManager()
{
    m_bRunning = false;
    if (m_thHandle && m_thHandle->joinable())
        m_thHandle->join();
    if (m_logQueue)
        delete m_logQueue;
}

bool LogManager::setLogFilepath(std::string filename)
{
    unsigned long long pos = filename.rfind('/');
#if defined(_WIN32)
    if (pos == std::string::npos) {
        pos = filename.rfind('\\');
    }
#endif
    if (pos == std::string::npos) {
        return false;
    }

    // 递归创建日志目录
    xiso::filesystem::create_directory_recurse(filename.substr(0, pos));
    m_filepath  = filename.substr(0, pos + 1);
    m_filename  = filename.substr(pos + 1, filename.length());
    m_bWriteLog = true;
    return true;
}

void LogManager::setLogKeepDays(int keepDays)
{
    // 设置日志留存期限
    m_keepDays = keepDays;
}

void LogManager::setLoggingLevel(int level)
{
    // 设置日志打印级别
    m_logLevel = level;
}

void LogManager::logRecord(int level, const char *format, ...)
{
    if (!m_bRunning) {
        static char  buf[LOG_LINE_SIZE];
        std::va_list args;
        ::va_start(args, format);
#if defined(XISO_PLATFORM_LINUX)
        int n = vsnprintf(buf, LOG_LINE_SIZE, format, args);
#elif defined(XISO_PLATFORM_WINDOWS)
        int n = vsprintf_s(buf, LOG_LINE_SIZE, format, args);
#endif
        std::cout << buf;
        ::va_end(args);
        return;
    }

    LogMessage *log = nullptr;
    do {
        log = m_logQueue->getProducer();
    } while (log == nullptr);

    std::va_list args;
    ::va_start(args, format);
    log->setMessage(level, format, args);
    ::va_end(args);

    m_logQueue->putConsumer(log);
}

void LogManager::startLogging()
{
    m_bRunning = true;
    m_thHandle.reset(new std::thread(&LogManager::loggerWorkerThread, this));
}

void LogManager::openLogStream(int level)
{
    std::ostringstream oss;

    // 格式化时间字符串
    auto   tp    = std::chrono::high_resolution_clock::now();
    time_t timer = std::chrono::system_clock::to_time_t(tp);
    oss << m_filepath << m_filename;
    switch (level) {
        case LOG_LEVEL_ERROR:
            oss << "Error.log.";
            break;
        case LOG_LEVEL_WARN:
            oss << "Warn.log.";
            break;
        case LOG_LEVEL_INFO:
            oss << "Info.log.";
            break;
        case LOG_LEVEL_DEBUG:
        default:
            oss << "Debug.log.";
    }
    oss << std::put_time(std::localtime(&timer), "%Y%m%d");

    std::string logFileName = oss.str();
    m_logStream[level].open(logFileName, ios::in | ios::out | ios::app);
}

bool LogManager::removeLogFiles()
{
    auto checkTime = xiso::get_current_timestamp<chrono::seconds>();
    checkTime      = checkTime - m_keepDays * (24 * 60 * 60);

    xiso::filesystem::DirectoryContainer dirContainer(m_filepath.c_str());
    xiso::filesystem::DirectoryIterator  dirIter = dirContainer.iterator();
    for (dirIter.start(); !dirIter.isDone(); dirIter.toNext()) {
        xiso::filesystem::DirectoryEntry entry = dirIter.current();
        if (entry.file_name() == "." || entry.file_name() == "..") {
            continue;
        }

        // 截取文件末尾字符串，并格式化为日期时间戳，进行当前时间的比较
        std::string filename = entry.file_name();
        if (!entry.is_directory() && str_startswith(filename, m_filename)) {
            int position = filename.rfind('.');

            struct tm timeinfo;
            memset(&timeinfo, 0, sizeof(timeinfo));
            timeinfo.tm_year = atoi(filename.substr(position + 1, 4).c_str()) - 1900;
            timeinfo.tm_mon  = atoi(filename.substr(position + 5, 2).c_str()) - 1;
            timeinfo.tm_mday = atoi(filename.substr(position + 7, 2).c_str());

            if (checkTime > mktime(&timeinfo)) {
                xiso::remove_file((m_filepath + filename).c_str());
            }
        }
    }
    return true;
}

void LogManager::loggerWorkerThread()
{
    while (m_bRunning) {
        auto curTime = xiso::get_current_timestamp<chrono::seconds>();
        if (curTime - m_lastTime > 86400) {
            m_lastTime = curTime - curTime % 86400 - 3600 * 8;

            auto iter = m_logStream.begin();
            for (; iter != m_logStream.end(); iter++) {
                if (iter->second.is_open())
                    iter->second.close();
            }

            if (m_keepDays > 0) {
                removeLogFiles();
            }
        }

        LogMessage *log = m_logQueue->getConsumer(1000);
        if (log == nullptr) {
            continue;
        }

        if (m_bWriteLog && log->level() >= m_logLevel) {
            if (!m_logStream[log->level()].is_open()) {
                openLogStream(log->level());
            }
            m_logStream[log->level()].write(log->getMessage(), log->length());
            m_logStream[log->level()].flush();
        } else {
            printf("%s", log->getMessage());
        }
        m_logQueue->putProducer(log);
    }
}
} // namespace log
} // namespace xiso