// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_string.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:27
//  描    述:
// =====================================================================================

#pragma once

#include <string>
#include <vector>

namespace kgr {

    /**
     * 十六进制数据转 hex
     * @param buf 十六进制数据
     * @param len 数据长度
     * @return hex 字符串
     */
    std::string bytes2hex_string(const unsigned char *buf, unsigned int len);

    /**
     * safe vsnprintf
     * @param dest
     * @param size bufsize
     * @param fmt 字符串格式化
     */
    int vsnprintf_safe(char *dest, int size, const char *fmt, ...);

    /**
     * 字符串分割
     * @param msg 原始字符串
     * @param separator
     */
    std::vector<std::string> string_split(const std::string &msg, std::string separator);

    /**
     * 去除左右两端字符
     * @param msg 原始字符串
     * @param ch 要修剪的字符
     * @return 修剪后的字符串
     */
    std::string string_trim(const std::string &msg, const char ch);

    /**
     * 字符串替换
     * @param string msg 原始字符串
     * @param string src 替换前的字符
     * @param string dst 替换后的字符
     */
    std::string string_replace(const std::string &msg, std::string src, std::string dst);

    /**
     * string 起始字符串判断
     * @param str 字符串
     * @param start 起始字符串
     * @return true/false
     */
    bool string_starts_with(const std::string &str, std::string start);

    /**
     * string 结束字符串判断
     * @param str 字符串
     * @param end 结束字符串
     * @return true/false
     */
    bool string_end_with(const std::string &str, std::string end);
} // namespace kgr