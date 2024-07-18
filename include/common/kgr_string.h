// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_string.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:27
//  描    述:
// =====================================================================================

#pragma once

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace kgr {
    /**
     * 浮点数按照精度转换为字符串类型
     * @param number 输入浮点型数字
     * @param limits 输出数字精度(整数加小数)
     * @return std::string 转换完成的字符串
     */
    template <typename T>
    std::string decimal2string(T number, int limits = 0)
    {
        int digits = limits > 0 ? limits : std::numeric_limits<T>::digits10;

        // 数字转字符串
        std::ostringstream oss;
        oss.precision(digits);
        oss << std::setbase(10) << number;
        std::string strNum = oss.str();

        // 小数部分处理
        if (strNum.find('.') != std::string::npos) {
            std::string::reverse_iterator rit = strNum.rbegin();
            while (rit != strNum.rend()) {
                if (*rit != '0') {
                    if (*rit == '.')
                        rit++;
                    break;
                }
                rit++;
            }

            if (rit != strNum.rbegin()) {
                std::string::iterator it = rit.base();
                strNum.erase(it, strNum.end());
            }
        }
        return strNum;
    }

    /**
     * 十六进制数据转 hex
     * @param buf 十六进制数据
     * @param len 数据长度
     * @return hex 字符串
     */
    std::string bytes2hexstr(const unsigned char *buf, unsigned int len);

    /**
     * hex 字符串转 byte 数组
     * @param dst
     * @param dstLen 最大长度
     * @param src 源数据
     * @param srcLen 源数据长度
     * @return 实际数据长度
     */
    int hexstr2bytes(unsigned char *dst, unsigned int dstLen, const char *src, unsigned int srcLen);

    /**
     * 字符串格式化
     * @param fmt 字符串格式化
     */
    std::string str_format(const char *fmt, ...);

    /**
     * 字符串分割
     * @param msg 原始字符串
     * @param separator 分隔符
     */
    std::vector<std::string> str_split(const std::string &msg, std::string separator);

    /**
     * @brief 修剪左右两端字符
     *
     * @param msg 原始字符串
     * @param ch 要修剪的字符
     * @return std::string 修剪后的字符串
     */
    std::string str_trim(const std::string &msg, const char ch);

    /**
     * 字符串替换
     * @param string msg 原始字符串
     * @param string src 替换前的字符
     * @param string dst 替换后的字符
     */
    std::string str_replace(const std::string &msg, std::string src, std::string dst);

    /**
     * string 起始字符串判断
     * @param str 字符串
     * @param start 起始字符串
     * @return true/false
     */
    bool str_startswith(const std::string &str, std::string start);

    /**
     * string 结束字符串判断
     * @param str 字符串
     * @param end 结束字符串
     * @return true/false
     */
    bool str_endswith(const std::string &str, std::string end);
} // namespace kgr