// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_math.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:29:21
//  描    述:
// =====================================================================================

#pragma once

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

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
} // namespace kgr