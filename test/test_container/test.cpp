#include "test.h"

#include "sync_queue.h"
#include "xiso_assert.h"

#include <iostream>
#include <sstream>
#include <string>
#include <thread>

void test_sync_queue()
{
    constexpr static int                    thread_num = 10;
    constexpr static int                    write_num  = 10000;
    xiso::container::SyncQueue<std::string> data_queue;
    std::thread                             thread_list[thread_num];
    for (int i = 0; i < thread_num; i++) {
        thread_list[i] = std::thread([&]() {
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            for (int i = 0; i < write_num; i++) {
                data_queue.push_back(oss.str() + "-" + std::to_string(i));
            }
        });
    }

    for (int i = 0; i < thread_num; i++) {
        if (thread_list[i].joinable()) {
            thread_list[i].join();
        }
    }

    int count = 0;
    while (!data_queue.empty()) {
        std::string data;
        data_queue.pop_front(data);
        ++count;
    }

    xiso_assert_equal(thread_num * write_num, count);
}

struct testcase_t main_testcases[] = {{test_sync_queue}, END_OF_TESTCASES};