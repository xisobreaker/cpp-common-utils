// =====================================================================================
//  Copyright (C) 2025 by Jiaxing Shao. All rights reserved

//  文 件 名:  xiso_random.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间：  2025-07-22 11:07
//  描    述:
// =====================================================================================

#pragma once

#include <cstdint>
#include <random>

namespace xiso {

class Random
{
public:
    Random();
    explicit Random(uint64_t seed);
    ~Random();

public:
    uint32_t random(uint32_t min, uint32_t max);

private:
    std::default_random_engine engine_;
};

} // namespace xiso