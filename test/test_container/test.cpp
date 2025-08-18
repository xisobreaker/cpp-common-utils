#include "test.h"

#include "free_queue.h"
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
    }

    for (int i = 0; i < thread_num; i++) {
        if (thread_list[i].joinable()) {
            thread_list[i].join();
        }
    }

    xiso_assert_equal(write_num * thread_num, count);
}

void test_free_queue()
{
    using thread_ptr = std::shared_ptr<std::thread>;
    xiso::container::LockFreeQueue<int> queue;

    bool stopflag    = false;
    int  ithread_num = 20;
    int  othread_num = 1;
    int  enqueue_num = 100000;

    std::vector<thread_ptr> enqueue_th(ithread_num);
    std::vector<thread_ptr> dequeue_th(othread_num);

    for (int i = 0; i < ithread_num; ++i) {
        enqueue_th[i].reset(new std::thread([&]() {
            for (int i = 0; i < enqueue_num; ++i) {
                queue.safe_enqueue(i);
            }
        }));
    }
    for (int i = 0; i < othread_num; ++i) {
        dequeue_th[i].reset(new std::thread([&]() {
            int count = 0;
            while (!stopflag || !queue.empty()) {
                auto v = queue.dequeue();
                if (v)
                    count += 1;
            }
            spdlog::info("total: {}", count);
            xiso_assert_equal(ithread_num * enqueue_num, count);
        }));
    }

    // 等待线程结束
    for (int i = 0; i < ithread_num; ++i) {
        if (enqueue_th[i]->joinable())
            enqueue_th[i]->join();
    }
    stopflag = true;
    for (int i = 0; i < othread_num; ++i) {
        if (dequeue_th[i]->joinable())
            dequeue_th[i]->join();
    }
}

struct testcase_t main_testcases[] = {{test_sync_queue}, {test_sync_queue2}, {test_sync_queue3}, {test_free_queue}, END_OF_TESTCASES};