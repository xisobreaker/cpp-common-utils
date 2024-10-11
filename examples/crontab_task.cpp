#include "scheduled.h"
#include "xiso_timer.h"

#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
    xiso::Scheduled scheduled;
    scheduled.addTask(
        []() {
            std::cout << xiso::get_current_timestamp<std::chrono::milliseconds>() << ", Hello, World!" << std::endl;
        },
        std::chrono::milliseconds(1000),
        true);
    scheduled.addTask(
        []() {
            std::cout << xiso::get_current_timestamp<std::chrono::milliseconds>() << ", Hello, Task!" << std::endl;
        },
        std::chrono::system_clock::now() + std::chrono::milliseconds(5000));

    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return 0;
}