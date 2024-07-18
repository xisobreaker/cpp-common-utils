// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  log_constants.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 18:05:52
//  描    述:
// =====================================================================================

#pragma once

namespace kgr {
namespace log {

static constexpr int LOG_LINE_SIZE  = 1024 * 128; // 单行日志大小, 128kb
static constexpr int LOG_QUEUE_SIZE = 1024 * 1;   // Log 队列长度

} // namespace log
} // namespace kgr