#include "test_crypto.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " [des/md5/base64] [message]" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "base64") == 0) {
        test_base64(argv[2], strlen(argv[2]));
    } else if (strcmp(argv[1], "md5") == 0) {
        test_md5(argv[2], strlen(argv[2]));
    } else if (strcmp(argv[1], "des") == 0) {
        test_des(argv[2], strlen(argv[2]));
    }
    return 0;
}