// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  xiso_file.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:37
//  描    述:
// =====================================================================================

#pragma once

#include <string>

namespace xiso {

/**
 * @brief 获取当前系统文件分隔符
 *
 * @return std::string 文件路径分隔符
 */
std::string os_path_separator();

/**
 * @brief 从文件路径截取文件名
 *
 * @param filepath 完整文件路径
 * @return const char* 返回文件名
 */
const char *extract_file_name(const char *filepath);

/**
 * @brief 判断文件是否存在
 *
 * @param filepath 文件路径
 * @return true
 * @return false
 */
bool file_is_exists(const char *filepath);

/**
 * @brief 判断文件夹是否存在
 *
 * @param directory 文件路径
 * @return true
 * @return false
 */
bool path_is_exists(const char *directory);

/**
 * @brief 检查目录是否存在, 不存在则创建
 *
 * @param directory
 */
void create_directory(const char *directory);

/**
 * @brief 删除目标文件夹
 *
 * @param directory 文件夹路径
 * @return true
 * @return false
 */
bool remove_directory(const char *directory);

/**
 * @brief 删除目标文件
 *
 * @param filepath 文件路径
 * @return true
 * @return false
 */
bool remove_file(const char *filepath);

} // namespace xiso