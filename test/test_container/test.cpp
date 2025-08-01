#include "test.h"

#include "sync_queue.h"
#include "xiso_assert.h"

#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
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

void test_sync_queue2()
{
    struct DataStruct {
        int value;
    };

    constexpr static int                                    queue_size = 20;
    constexpr static int                                    thread_num = 10;
    constexpr static int                                    write_num  = 10000;
    xiso::container::SyncQueue<std::shared_ptr<DataStruct>> data_queue(queue_size);
    std::thread                                             thread_list[thread_num];

    for (int i = 0; i < thread_num; i++) {
        thread_list[i] = std::thread([&]() {
            for (int i = 0; i < write_num; i++) {
                auto data   = std::make_shared<DataStruct>();
                data->value = i;
                data_queue.push_back(data);
            }
        });
    }

    int waitTime = 0;
    do {
        xiso_assert_le(data_queue.size(), queue_size);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while ((waitTime++) != 10);

    for (int i = 0; i < thread_num; i++) {
        if (thread_list[i].joinable()) {
            thread_list[i].join();
        }
    }
}

void test_sync_queue3()
{
    struct DataStruct {
        int value;
    };

    constexpr static int queue_size = 100000;
    constexpr static int thread_num = 10;
    constexpr static int write_num  = 10000;

    xiso::container::SyncQueue<std::shared_ptr<DataStruct>> data_queue(queue_size);
    std::thread                                             thread_list[thread_num];

    for (int i = 0; i < thread_num; i++) {
        thread_list[i] = std::thread([&]() {
            for (int i = 0; i < write_num; i++) {
                auto data   = std::make_shared<DataStruct>();
                data->value = i;
                data_queue.push_back(data);
            }
        });
    }

    int count = 0;
    while (count != write_num * thread_num) {
        std::shared_ptr<DataStruct> data;
        data_queue.wait_pop_front(data, 100);
        ++count;
        spdlog::info("{}, remain: {}", count, data_queue.size());
    }

    for (int i = 0; i < thread_num; i++) {
        if (thread_list[i].joinable()) {
            thread_list[i].join();
        }
    }
}

struct testcase_t main_testcases[] = {{test_sync_queue}, {test_sync_queue2}, {test_sync_queue3}, END_OF_TESTCASES};