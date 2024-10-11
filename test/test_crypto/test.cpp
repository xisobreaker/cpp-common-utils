#include "test.h"

#include "base64.h"
#include "des.h"
#include "md5.h"
#include "xiso_assert.h"

#include <cstring>
#include <iostream>
#include <memory>

void test_md5()
{
    const char *message = "Hello, World!";
    int         length  = strlen(message);

    std::string output = xiso::crypto::md5_encrypt_hex((unsigned char *)message, length);
    xiso_assert_strequal(output.c_str(), "65a8e27d8879283831b664bd8b7f0ad4");
}

void test_des()
{
    char                    key[] = "abcdefgh1234567822345678";
    xiso::crypto::DesCrypto des;
    const char             *message = "Hello, World!";
    int                     length  = strlen(message);

    // 初始化密钥
    des.initSecretKey(key, strlen(key), true, xiso::crypto::PaddingType::ZeroPadding);

    // 数据加密
    std::string output = des.encryptBase64(message, length);

    // 数据源
    std::shared_ptr<char[]> source(new char[length + 1]);
    des.decryptBase64(output, source.get(), length + 1);

    xiso_assert_strequal(message, source.get());
}

void test_base64()
{
    const char             *message = "Hello, World!";
    int                     length  = strlen(message);
    std::shared_ptr<char[]> source(new char[length + 1]);
    std::shared_ptr<char[]> output(new char[length * 2 + 1]);

    int outlen = xiso::crypto::base64_encode(output.get(), length * 2 + 1, message, length);
    int srclen = xiso::crypto::base64_decode(source.get(), length + 1, output.get(), outlen);

    xiso_assert_strequal(message, source.get());
}

struct testcase_t main_testcases[] = {{test_md5}, {test_des}, {test_base64}, END_OF_TESTCASES};