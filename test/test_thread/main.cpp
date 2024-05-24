#include "threadpool.h"
#include "threadtask.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using namespace std;

int main(int argc, char *argv[])
{
    kgr::thread::ThreadPool pool(8);
    pool.start();

    for (int i = 0; i < 10000; i++) {
        std::shared_ptr<kgr::thread::IThreadTask> task;
        task = std::make_shared<kgr::thread::ThreadTask<std::string>>(
            [](std::string value) {
                std::cout << "hello, " << value << std::endl;
            },
            to_string(i));
        pool.addTask(task);
    }

    while (pool.taskSize() > 0) {
        std::this_thread::sleep_for(chrono::milliseconds(100));
    }
    pool.stop();

    return 0;
}