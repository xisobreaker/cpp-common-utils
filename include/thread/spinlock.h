#pragma once

#include <atomic>

namespace xiso {

class SpinLock
{
public:
    SpinLock() : flag(ATOMIC_FLAG_INIT){};

public:
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() { flag.clear(std::memory_order_release); }

private:
    std::atomic_flag flag;
};

} // namespace xiso