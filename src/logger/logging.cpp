#include "logging.h"

namespace xiso {
namespace log {

bool init_log_manager(std::string filename, int keepDays, int level)
{
    LogManager *logManager = LogManager::getInstance();
    if (!logManager->setLogFilepath(filename)) {
        return false;
    }
    logManager->setLogKeepDays(keepDays);
    logManager->setLoggingLevel(level);
    logManager->startLogging();
    return true;
}

} // namespace log
} // namespace xiso