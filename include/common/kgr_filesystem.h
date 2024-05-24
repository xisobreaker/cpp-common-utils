// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_filesystem.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:37
//  描    述:
// =====================================================================================

#pragma once

#include <string>

namespace kgr {
    namespace filesystem {
        /**
         * 获取系统文件分隔符
         * @return 文件路径分隔符
         */
        std::string os_path_separator();

        /**
         * 从文件路径截取文件名
         * @param 完整文件路径
         * @return 返回文件名
         */
        const char *extract_file_name(const char *filepath);

        /**
         * 判断文件是否存在
         * @param path 文件路径
         * @return true/false
         */
        bool file_is_exists(const char *filepath);

        /**
         * 判断文件夹是否存在
         * @param path 文件路径
         * @return true/false
         */
        bool path_is_exists(const char *directory);

        /**
         * 检查目录是否存在, 不存在则创建
         * @param directory 文件夹路径
         */
        void create_directory(const char *directory);

        /**
         * 删除目标文件夹
         * @param directory 文件夹路径
         * @return true/false
         */
        bool remove_directory(const char *directory);

        /**
         * 删除目标文件
         * @param directory 文件路径
         * @return true/false
         */
        bool remove_file(const char *filepath);

        /**
         * 递归创建文件夹
         * @param directory 文件夹路径
         */
        void create_directory_recurse(const std::string &directory);

        /**
         * 递归删除目标路径下所有文件
         * @param directory 文件夹路径
         * @return true/false
         */
        bool remove_directory_recurse(const char *directory);
    } // namespace filesystem
} // namespace kgr