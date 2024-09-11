#include "test.h"

#include "base64.h"
#include "des.h"
#include "kgr_assert.h"
#include "md5.h"

#include <cstring>
#include <iostream>
#include <memory>

void test_md5()
{
    const char *message = "Hello, World!";
    int         length  = strlen(message);

    std::string output = kgr::crypto::md5_encrypt_hex((unsigned char *)message, length);
    kgr_assert_strequal(output.c_str(), "65a8e27d8879283831b664bd8b7f0ad4");
}

void test_des()
{
    char                   key[] = "abcdefgh1234567822345678";
    kgr::crypto::DesCrypto des;
    const char            *message = "Hello, World!";
    int                    length  = strlen(message);

    // 初始化密钥
    des.initSecretKey(key, strlen(key), true, kgr::crypto::PaddingType::ZeroPadding);

    // 数据加密
    std::string output = des.encryptBase64(message, length);

    // 数据源
    std::shared_ptr<char[]> source(new char[length + 1]);
    des.decryptBase64(output, source.get(), length + 1);

    kgr_assert_strequal(message, source.get());
}

void test_base64()
{
    const char             *message = "Hello, World!";
    int                     length  = strlen(message);
    std::shared_ptr<char[]> source(new char[length + 1]);
    std::shared_ptr<char[]> output(new char[length * 2 + 1]);

    int outlen = kgr::crypto::base64_encode(output.get(), length * 2 + 1, message, length);
    int srclen = kgr::crypto::base64_decode(source.get(), length + 1, output.get(), outlen);

    kgr_assert_strequal(message, source.get());
}

struct testcase_t main_testcases[] = {{test_md5}, {test_des}, {test_base64}, END_OF_TESTCASES};