#include "log_manager.h"

#include "kgr_filesystem.h"
#include "kgr_string.h"
#include "kgr_timer.h"
#include "log_queue.h"

#include <chrono>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

namespace kgr {
    namespace log {
        LogManager *g_logManager = new LogManager();

        LogManager::LogManager()
        {
            m_bRunning  = true;
            m_bWriteLog = false;
            m_logLevel  = LOG_LEVEL_INFO;
            m_keepDays  = 0;
            m_lastTime  = 0;
            m_logQueue  = new LogQueue();
            m_thHandle  = std::thread(&LogManager::loggerWorkerThread, this);
        }

        LogManager::~LogManager()
        {
            m_bRunning = false;
            if (m_thHandle.joinable())
                m_thHandle.join();
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
            kgr::create_directory_recurse(filename.substr(0, pos));
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

        void LogManager::openLogFile(int level)
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
            auto checkTime = kgr::get_current_timestamp<chrono::seconds>();
            checkTime      = checkTime - m_keepDays * (24 * 60 * 60);

            kgr::DirectoryContainer dirContainer(m_filepath.c_str());
            kgr::DirectoryIterator  dirIter = dirContainer.iterator();
            for (dirIter.start(); !dirIter.isDone(); dirIter.toNext()) {
                kgr::DirectoryEntry entry = dirIter.current();
                if (entry.file_name() == "." || entry.file_name() == "..") {
                    continue;
                }

                std::string filename = entry.file_name();
                if (!entry.is_directory() && string_starts_with(filename, m_filename)) {
                    int position = filename.rfind('.');

                    struct tm timeinfo;
                    timeinfo.tm_year = atoi(filename.substr(position + 1, 4).c_str()) - 1900;
                    timeinfo.tm_mon  = atoi(filename.substr(position + 5, 2).c_str()) - 1;
                    timeinfo.tm_mday = atoi(filename.substr(position + 7, 2).c_str());

                    if (checkTime > mktime(&timeinfo)) {
                        kgr::remove_file((m_filepath + filename).c_str());
                    }
                }
            }
            return true;
        }

        void LogManager::loggerWorkerThread()
        {
            while (m_bRunning) {
                auto curTime = kgr::get_current_timestamp<chrono::seconds>();
                if (curTime - m_lastTime > 86400) {
                    m_lastTime = curTime - curTime % 86400;

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
                        openLogFile(log->level());
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
} // namespace kgr