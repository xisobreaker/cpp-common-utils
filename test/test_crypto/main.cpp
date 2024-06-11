#include "test_crypto.h"

#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    test_base64();
    test_md5();
    test_des();
    return 0;
}