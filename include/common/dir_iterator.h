// =====================================================================================
//  Copyright (C) 2024 by Jiaxing Shao. All rights reserved
//
//  文 件 名:  dir_iterator.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间:  2024-05-24 17:28:30
//  描    述:
// =====================================================================================

#pragma once

#if defined(__linux__)
    #include <dirent.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

#include <string>

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
#if defined(__linux__)
    DirectoryEntry(dirent *entry);
#elif defined(_WIN32)
    DirectoryEntry(WIN32_FIND_DATA entry);
#endif
    ~DirectoryEntry();

public:
    bool        is_directory();
    std::string file_name();

private:
#if defined(__linux__)
    struct dirent *m_entry;
#elif defined(_WIN32)
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
#if defined(__linux__)
    DIR           *m_dirHandler;
    struct dirent *m_entry;
#elif defined(_WIN32)
    HANDLE          m_dirHandler;
    WIN32_FIND_DATA m_entry;
    bool            m_successful;
#endif
    DirectoryContainer *m_container;
};
