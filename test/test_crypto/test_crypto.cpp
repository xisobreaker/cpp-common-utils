#include "test_crypto.h"

#include "base64.h"
#include "des.h"
#include "md5.h"

#include <cstring>
#include <iostream>
#include <memory>

void test_md5(const char *message, unsigned int length)
{
    std::cout << "md5 source:  " << message << std::endl;
    std::string output = kgr::crypto::md5_encrypt_hex((unsigned char *)message, length);
    std::cout << "md5 encrypt: " << output << std::endl;
}

void test_des(const char *message, unsigned int length)
{
    char                   key[] = "abcdefgh1234567822345678";
    kgr::crypto::DesCrypto des;

    std::cout << "3des key: " << key << std::endl;
    des.initSecretKey(key, strlen(key), true, kgr::crypto::PaddingType::ZeroPadding);

    std::cout << "3des source: " << message << std::endl;
    std::string output = des.encryptBase64(message, length);
    std::cout << "3des encode: " << output << std::endl;

    std::shared_ptr<char[]> source(new char[length + 1]);
    des.decryptBase64(output, source.get(), length + 1);
    std::cout << "3des decode: " << source << std::endl;
}

void test_base64(const char *message, unsigned int length)
{
    std::shared_ptr<char[]> source(new char[length + 1]);
    std::shared_ptr<char[]> output(new char[length * 2]);
    std::cout << "base64 source: " << message << std::endl;

    int outlen = kgr::crypto::base64_encode(message, length, output.get(), length * 2);
    std::cout << "base64 encode: " << output << std::endl;

    int srclen = kgr::crypto::base64_decode(output.get(), outlen, source.get(), length + 1);
    std::cout << "base64 decode: " << source << std::endl;
}
