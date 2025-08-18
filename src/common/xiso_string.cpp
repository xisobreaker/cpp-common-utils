#include "xiso_string.h"

#include "config/platform.h"

#include <cstdarg>
#include <cstring>

namespace xiso {

std::string bytes2hexstr(const unsigned char *buf, unsigned int len)
{
    static const char hex_table[] = "0123456789ABCDEF";

    if (buf == nullptr)
        return "";

    std::string message;
    message.reserve(len * 3);
    for (int i = 0; i < len; i++) {
        unsigned char byte = buf[i];
        message.push_back(hex_table[(byte >> 4) & 0x0F]);
        message.push_back(hex_table[byte & 0x0F]);
        if (i + 1 != len)
            message.push_back(' ');
    }
    return message;
}

int hexstr2bytes(unsigned char *dst, const char *src, unsigned int srcLen)
{
    auto hex_value = [](char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        }
        return 0;
    };

    int length = 0;
    int chSize = 0;
    for (int i = 0; i < srcLen; i++) {
        if (src[i] == ' ')
            continue;

        if ((chSize++) % 2 == 0) {
            dst[length] += (hex_value(src[i]) << 4);
        } else {
            dst[length++] += hex_value(src[i]);
        }
    }
    return length;
}

std::string str_format(const char *fmt, ...)
{
    char    buf[4096] = {0};
    va_list args;
    va_start(args, fmt);
#if defined(XISO_PLATFORM_LINUX)
    int n = vsnprintf(buf, 4096, fmt, args);
#elif defined(XISO_PLATFORM_WINDOWS)
    int n = vsprintf_s(buf, 4096, fmt, args);
#endif
    va_end(args);
    return std::string(buf);
}

std::vector<std::string> str_split(const std::string &msg, std::string separator)
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

char *str_split_values(char *str, char sep, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*str == sep)
        str++;

    while (*fmt) {
        char         **s, *tmp;
        int           *i;
        long long int *l;
        time_t        *t;

        switch (*fmt++) {
            case 's':
                s   = va_arg(args, char **);
                *s  = str;
                tmp = strchr(str, sep);
                if (tmp) {
                    while (*tmp == sep) {
                        *tmp++ = '\0';
                    }
                    str = tmp;
                } else {
                    str = &str[strlen(str)];
                }
                break;
            case 'l':
                l  = va_arg(args, long long int *);
                *l = strtoll(str, &tmp, 10);
                if (tmp == str) {
                    *str = 0;
                } else {
                    str = tmp;
                }
                break;
            case 'i':
                i  = va_arg(args, int *);
                *i = strtol(str, &tmp, 10);
                if (tmp == str) {
                    *str = 0;
                } else {
                    str = tmp;
                }
                break;
            case 't':
                t  = va_arg(args, time_t *);
                *t = strtol(str, &tmp, 10);
                if (tmp == str) {
                    *str = 0;
                } else {
                    str = tmp;
                    switch (*str) {
                        case 'd':
                            *t *= 86400;
                            (*str)++;
                            break;
                        case 'h':
                            *t *= 3600;
                            (*str)++;
                            break;
                        case 'm':
                            *t *= 60;
                            (*str)++;
                            break;
                    }
                }
                break;
        }

        while (*str == sep) {
            str++;
        }
    }
    va_end(args);
    return str;
}

std::string str_trim(const std::string &msg, const char ch)
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

std::string str_replace(const std::string &msg, std::string src, std::string dst)
{
    std::string message = msg;
    while (message.find(src) != std::string::npos) {
        message.replace(message.find(src), src.length(), dst);
    }
    return message;
}

bool str_startswith(const std::string &str, std::string start)
{
    auto startLen = start.length();
    if (str.length() >= startLen) {
        std::string temp = str.substr(0, startLen);
        return temp.compare(start) == 0;
    }
    return false;
}

bool str_endswith(const std::string &str, std::string end)
{
    auto endLen = end.length();
    if (str.length() >= endLen) {
        std::string temp = str.substr(str.length() - endLen, str.length());
        return temp.compare(end) == 0;
    }
    return false;
}

bool split_http_url(std::string &domain, std::string &route, const std::string &httpurl)
{
    if (!str_startswith(httpurl, "http:") && !str_startswith(httpurl, "https:")) {
        return false;
    }

    int pos = httpurl.find_first_of("/");
    pos     = httpurl.find_first_of("/", pos + 2);
    if (pos == std::string::npos) {
        domain = httpurl;
        route  = "/";
        return true;
    }
    domain = httpurl.substr(0, pos);
    route  = httpurl.substr(pos);
    return true;
}
} // namespace xiso
