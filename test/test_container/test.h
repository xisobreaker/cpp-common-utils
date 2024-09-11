#pragma once

typedef void (*testcase_fn)();

struct testcase_t {
    testcase_fn func;
};

#define END_OF_TESTCASES \
    {                    \
        NULL             \
    }

extern struct testcase_t main_testcases[];