// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  base64.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:27:26
//  描    述:
// =====================================================================================

#ifndef _BASE64_H_H_H
#define _BASE64_H_H_H

namespace xiso {
namespace crypto {

/**
 * @brief base64编码
 *
 * @param dstBuf 编码完成后的数据
 * @param dstMaxLen dstBuf缓存最大长度
 * @param srcBuf 需要进行 base64 编码的原始数据
 * @param srcLen 原始数据长度
 * @return int
 */
int base64_encode(char *dstBuf, int dstMaxLen, const char *srcBuf, int srcLen);

/**
 * @brief base64解码
 *
 * @param dstBuf 解码完成后的数据
 * @param dstMaxLen dstBuf缓存最大长度
 * @param srcBuf 需要进行 base64 解码的原始数据
 * @param srcLen 原始数据长度
 * @return int
 */
int base64_decode(char *dstBuf, int dstMaxLen, const char *srcBuf, int srcLen);

} // namespace crypto
} // namespace xiso

#endif
