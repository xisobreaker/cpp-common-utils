// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_filesystem.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-06-11 16:35:18
//  描    述:
// =====================================================================================

#pragma once

#include <string>

namespace kgr {
namespace filesystem {

/**
 * @brief 递归创建文件夹
 *
 * @param directory 文件夹路径
 */
void create_directory_recurse(const std::string &directory);

/**
 * @brief 递归删除目标路径下所有文件
 *
 * @param directory 文件夹路径
 * @return true
 * @return false
 */
bool remove_directory_recurse(const char *directory);

} // namespace filesystem
} // namespace kgr