#pragma once

#include <cstring>
#include <exception>
#include <memory>
#include <string>

namespace xiso {

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
        int length = snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
        errmsg_    = std::shared_ptr<char>(new char[length], std::default_delete<char[]>());
        snprintf(errmsg_.get(), length, fmt.c_str(), std::forward<Args>(args)...);
    }

    virtual char const *what() const noexcept
    {
        return errmsg_.get();
    }

private:
    std::shared_ptr<char> errmsg_;
};

} // namespace xiso
