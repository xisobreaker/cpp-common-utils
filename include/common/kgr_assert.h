#pragma once

#include <cassert>
#include <cstring>

namespace kgr {
    template <typename T>
    void assert_equal(T a, T b)
    {
        assert(a == b);
    }

    inline void assert_strequal(const char *a, const char *b)
    {
        assert(strcmp(a, b) == 0);
    }
} // namespace kgr