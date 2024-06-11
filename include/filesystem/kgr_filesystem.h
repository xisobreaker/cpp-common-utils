#pragma once

#include <string>

namespace kgr {
    namespace filesystem {

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