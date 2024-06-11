// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  kgr_diriterator.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-06-11 16:35:12
//  描    述:
// =====================================================================================

#pragma once

#include "config/platform.h"

#include <string>

#if defined(KGR_PLATFORM_LINUX)
    #include <dirent.h>
#elif defined(KGR_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

namespace kgr {
    namespace filesystem {
        class DirectoryIterator;
        class DirectoryContainer
        {
            friend class DirectoryIterator;

        public:
            DirectoryContainer(const char *directory);
            ~DirectoryContainer();

        public:
            std::string       filepath();
            DirectoryIterator iterator();

        private:
            std::string m_directory;
        };

        class DirectoryEntry
        {
        public:
#if defined(KGR_PLATFORM_LINUX)
            DirectoryEntry(dirent *entry);
#elif defined(KGR_PLATFORM_WINDOWS)
            DirectoryEntry(WIN32_FIND_DATA entry);
#endif
            ~DirectoryEntry();

        public:
            bool        is_directory();
            std::string file_name();

        private:
#if defined(KGR_PLATFORM_LINUX)
            struct dirent *m_entry;
#elif defined(KGR_PLATFORM_WINDOWS)
            WIN32_FIND_DATA m_entry;
#endif
        };

        class DirectoryIterator
        {
        public:
            DirectoryIterator(DirectoryContainer *container);
            ~DirectoryIterator();

        public:
            void start();
            void toNext();
            bool isDone();

            DirectoryEntry current();

        private:
#if defined(KGR_PLATFORM_LINUX)
            DIR           *m_dirHandler;
            struct dirent *m_entry;
#elif defined(KGR_PLATFORM_WINDOWS)
            HANDLE          m_dirHandler;
            WIN32_FIND_DATA m_entry;
            bool            m_successful;
#endif
            DirectoryContainer *m_container;
        };
    } // namespace filesystem
} // namespace kgr