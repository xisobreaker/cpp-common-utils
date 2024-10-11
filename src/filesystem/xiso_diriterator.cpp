#include "xiso_diriterator.h"

namespace xiso {
namespace filesystem {

DirectoryContainer::DirectoryContainer(const char *directory) : m_directory(directory)
{
}

DirectoryContainer::~DirectoryContainer()
{
}

std::string DirectoryContainer::filepath()
{
    return m_directory;
}

DirectoryIterator DirectoryContainer::iterator()
{
    return DirectoryIterator(this);
}

/*********************************** DirectoryEntry ***********************************/

DirectoryEntry::~DirectoryEntry()
{
}

#if defined(XISO_PLATFORM_LINUX)
DirectoryEntry::DirectoryEntry(dirent *entry)
{
    m_entry = entry;
}

bool DirectoryEntry::is_directory()
{
    return m_entry->d_type == DT_DIR;
}

std::string DirectoryEntry::file_name()
{
    return std::string(m_entry->d_name);
}

#elif defined(XISO_PLATFORM_WINDOWS)
DirectoryEntry::DirectoryEntry(WIN32_FIND_DATA entry)
{
    m_entry = entry;
}

bool DirectoryEntry::is_directory()
{
    return (m_entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

std::string DirectoryEntry::file_name()
{
    return std::string(m_entry.cFileName);
}
#endif

/*********************************** DirectoryIterator ***********************************/

DirectoryIterator::DirectoryIterator(DirectoryContainer *container)
{
    m_container = container;
#if defined(XISO_PLATFORM_LINUX)
    m_dirHandler = nullptr;
    m_entry      = nullptr;
#elif defined(XISO_PLATFORM_WINDOWS)
    m_dirHandler = 0;
    m_successful = false;
#endif
}

DirectoryIterator::~DirectoryIterator()
{
    if (m_dirHandler) {
#if defined(XISO_PLATFORM_LINUX)
        closedir(m_dirHandler);
#elif defined(XISO_PLATFORM_WINDOWS)
        FindClose(m_dirHandler);
#endif
    }
}

#if defined(XISO_PLATFORM_LINUX)
void DirectoryIterator::start()
{
    m_dirHandler = opendir(m_container->m_directory.c_str());
    if (m_dirHandler != nullptr) {
        toNext();
    }
}

void DirectoryIterator::toNext()
{
    m_entry = readdir(m_dirHandler);
}

bool DirectoryIterator::isDone()
{
    return m_entry == nullptr;
}

#elif defined(XISO_PLATFORM_WINDOWS)
void DirectoryIterator::start()
{
    std::string findpath = m_container->m_directory;
    if (findpath.back() == '\\') {
        findpath = findpath + "*";
    } else {
        findpath = findpath + "\\*";
    }
    m_dirHandler = FindFirstFile(findpath.c_str(), &m_entry);
    if (m_dirHandler != INVALID_HANDLE_VALUE) {
        m_successful = true;
    }
}

void DirectoryIterator::toNext()
{
    m_successful = FindNextFile(m_dirHandler, &m_entry);
}

bool DirectoryIterator::isDone()
{
    return !m_successful;
}
#endif

DirectoryEntry DirectoryIterator::current()
{
    return DirectoryEntry(m_entry);
}
} // namespace filesystem
} // namespace xiso