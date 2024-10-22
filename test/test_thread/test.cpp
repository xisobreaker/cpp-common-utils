#include "test.h"

#include "scheduled.h"

#include <chrono>
#include <iostream>

void test_threadpool()
{
    std::cout << "test_threadpool" << std::endl;
}

void test_scheduled()
{
    xiso::Scheduled cron;
    cron.addTask(
        []() {
            std::cout << "hello, world!" << std::endl;
        },
        std::chrono::milliseconds(100));
}

struct testcase_t main_testcases[] = {{test_threadpool}, {test_scheduled}, END_OF_TESTCASES};