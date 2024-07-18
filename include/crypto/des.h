// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  des.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:27:19
//  描    述:
// =====================================================================================

#ifndef _DES_ENCRYPT_H_H_H
#define _DES_ENCRYPT_H_H_H

#include <string>
namespace kgr {
namespace crypto {
enum PaddingType {
    ZeroPadding  = 0,
    Pkcs5Padding = 1,
    Pkcs7Padding = 2
};

struct SecretKey {
    bool is3DES;
    bool subKey[3][16][48];
};

class DesCrypto
{
public:
    DesCrypto();
    ~DesCrypto();

private:
    void         byteToBinary(char ch, bool binary[8]);
    void         keyLeftShift(bool key56[56], unsigned int round);
    void         f_function(bool r32[32], bool subKey[48], bool out32[32]);
    void         desEncode64(SecretKey *secretKey, const char *pBuf, char *pDst, int keyN);
    void         desDecode64(SecretKey *secretKey, const char *pBuf, char *pDst, int keyN);
    unsigned int desEncode(SecretKey *secretKey, const char *pBuf, unsigned int nLen, char *pDst, int keyN);
    unsigned int desDecode(SecretKey *secretKey, const char *pBuf, unsigned int nLen, char *pDst, int keyN);
    void         createSubKey(SecretKey *secretKey, char *pKey, int keyN);

public:
    void initSecretKey(const char *pKey, int nLen, bool is3Des, PaddingType padType);

    int encrypt(const char *srcBuf, int srcLen, char *dstBuf, int dstMaxLen);
    int decrypt(const char *srcBuf, int srcLen, char *dstBuf, int dstMaxLen);

    std::string encryptBase64(const char *pBuf, int nLen);
    int         decryptBase64(std::string &strMsg, char *pBuf, int nMaxLen);

private:
    SecretKey   m_secretKey;
    PaddingType m_paddingType;
};
} // namespace crypto
} // namespace kgr

#endif
