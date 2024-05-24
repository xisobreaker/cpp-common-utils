#include "logging.h"

namespace kgr {
    namespace log {
        bool init_log_manager(std::string filename, int keepDays, int level)
        {
            LogManager *logManager = LogManager::getInstance();
            if (!logManager->setLogFilepath(filename)) {
                return false;
            }
            logManager->setLogKeepDays(keepDays);
            logManager->setLoggingLevel(level);
            return true;
        }
    } // namespace log
} // namespace kgr