// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  md5.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:27:59
//  描    述:
// =====================================================================================

#ifndef _MD5_ENCRYPT_H_H_H
#define _MD5_ENCRYPT_H_H_H

#include <string>
namespace kgr {
    namespace crypto {
        /**
         * @param srcBuf 待加密数据
         * @param srcLen 待加密数据长度
         * @return 加密后的 hex 字符串
         */
        std::string md5_encrypt_hex(const unsigned char *srcBuf, int srcLen);
    } // namespace crypto
} // namespace kgr
#endif
