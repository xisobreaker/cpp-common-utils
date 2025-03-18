#pragma once

#include <chrono>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>

namespace xiso {

template <typename T>
struct item_return {
    using type = T &&;
};

template <>
struct item_return<std::string &> {
    using type = const char *;
};

template <>
struct item_return<std::string> {
    using type = const char *;
};

template <typename T>
inline typename item_return<T>::type convert(T &&arg)
{
    return static_cast<T &&>(arg);
}

template <>
inline typename item_return<std::string &>::type convert<std::string &>(std::string &arg)
{
    return static_cast<const char *>(arg.c_str());
}

template <>
inline typename item_return<std::string>::type convert<std::string>(std::string &&arg)
{
    return static_cast<const char *>(arg.c_str());
}

class XisoException : public std::exception
{
public:
    XisoException(const std::string &&fmt)
    {
        int length = fmt.length() + 1;
        errmsg_    = std::shared_ptr<char>(new char[length], std::default_delete<char[]>());
        memcpy(errmsg_.get(), fmt.c_str(), fmt.length());
    }

    template <typename... Args>
    explicit XisoException(const std::string &&fmt, Args &&...args)
    {
        int length = fmt.length() + sum_length(args...) + 1;
        errmsg_    = std::shared_ptr<char>(new char[length], std::default_delete<char[]>());
        snprintf(errmsg_.get(), length, fmt.c_str(), convert(std::forward<Args>(args))...);
    }

    virtual char const *what() const noexcept
    {
        return errmsg_.get();
    }

private:
    template <typename T>
    int sum_length(T value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str().length();
    }

    template <typename T, typename... Args>
    int sum_length(T value, Args &&...args)
    {
        std::ostringstream oss;
        oss << value;
        int length = sum_length(args...);
        return length + oss.str().length();
    }

private:
    std::shared_ptr<char> errmsg_;
};

} // namespace xiso
