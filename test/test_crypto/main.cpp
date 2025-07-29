#include "test.h"

int main(int argc, char *argv[])
{
    for (int i = 0; main_testcases[i].func; i++) {
        main_testcases[i].func();
    }
    return 0;
}