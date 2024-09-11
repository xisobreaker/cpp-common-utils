#include "test.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; main_testcases[i].func; i++) {
        main_testcases[i].func();
    }
    return 0;
}