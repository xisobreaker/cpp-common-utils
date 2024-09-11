#include "test.h"

#include <iostream>

void test_threadpool()
{
    std::cout << "test_threadpool" << std::endl;
}

struct testcase_t main_testcases[] = {{test_threadpool}, END_OF_TESTCASES};