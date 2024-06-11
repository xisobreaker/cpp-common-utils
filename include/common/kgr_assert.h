#pragma once

#include <cassert>
#include <cstring>

#define kgr_assert_equal(a, b) assert(a == b)

#define kgr_assert_strequal(a, b) assert(strcmp(a, b) == 0)
