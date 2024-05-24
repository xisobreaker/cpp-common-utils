#include "kgr_string.h"

#include "config/platform.h"

#include <cstdarg>

namespace kgr {

    std::string bytes2hex_string(const unsigned char *buf, unsigned int len)
    {
        // hex 转换表
        static const char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

        if (buf == nullptr)
            return "";

        std::string message;
        for (int i = 0; i < len; i++) {
            message += hex_table[buf[i] >> 4];
            message += hex_table[buf[i] & 0x0F];
            if (len > i + 1)
                message += ' ';
        }
        return message;
    }

    int vsnprintf_safe(char *dest, int size, const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
#if defined(KGR_PLATFORM_LINUX)
        int n = vsnprintf(dest, size, fmt, args);
#elif defined(KGR_PLATFORM_WINDOWS)
        int n = vsprintf_s(dest, size, fmt, args);
#endif
        va_end(args);
        return n;
    }

    std::vector<std::string> string_split(const std::string &msg, std::string separator)
    {
        std::vector<std::string> vecStrings;

        // start 起始位置, pos 分隔符位置
        int start = 0, pos = 0;
        while ((pos = msg.find(separator, start)) != std::string::npos) {
            if (start != pos)
                vecStrings.push_back(msg.substr(start, pos - start));
            start = pos + separator.length();
        }
        if (start != msg.length())
            vecStrings.push_back(msg.substr(start));
        return vecStrings;
    }

    std::string string_trim(const std::string &msg, const char ch)
    {
        std::string message = msg;
        while (message.length() > 0) {
            if (message[0] != ch) {
                break;
            }
            message.erase(0, 1);
        }

        while (message.length() > 0) {
            if (message[message.length() - 1] != ch)
                break;
            message.erase(message.length() - 1, message.length());
        }
        return message;
    }

    std::string string_replace(const std::string &msg, std::string src, std::string dst)
    {
        std::string message = msg;
        while (message.find(src) != std::string::npos) {
            message.replace(message.find(src), src.length(), dst);
        }
        return message;
    }

    bool string_starts_with(const std::string &str, std::string start)
    {
        auto startLen = start.length();
        if (str.length() >= startLen) {
            std::string temp = str.substr(0, startLen);
            return temp.compare(start) == 0;
        }
        return false;
    }

    bool string_end_with(const std::string &str, std::string end)
    {
        auto endLen = end.length();
        if (str.length() >= endLen) {
            std::string temp = str.substr(str.length() - endLen, str.length());
            return temp.compare(end) == 0;
        }
        return false;
    }
} // namespace kgr
