#include "test.h"

#include <iostream>

void test_create_directories()
{
    std::cout << "test_create_directories" << std::endl;
}

void test_remove_directories()
{
    std::cout << "test_remove_directories" << std::endl;
}

void test_directory_iterator()
{
    std::cout << "test_directory_iterator" << std::endl;
}

struct testcase_t main_testcases[] = {{test_create_directories}, {test_remove_directories}, {test_directory_iterator}, END_OF_TESTCASES};