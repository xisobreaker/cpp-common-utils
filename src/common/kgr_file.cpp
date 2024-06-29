#include "kgr_file.h"

#include "config/platform.h"

#include <cstring>
#include <string>

#if defined(KGR_PLATFORM_LINUX)
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
#elif defined(KGR_PLATFORM_WINDOWS)
    #include <Windows.h>
    #include <io.h>
#endif

namespace kgr {

    std::string os_path_separator()
    {
#if defined(KGR_PLATFORM_LINUX)
        return "/";
#elif defined(KGR_PLATFORM_WINDOWS)
        return "\\";
#endif
        return "";
    }

    const char *extract_file_name(const char *filepath)
    {
        const char *base = strrchr(filepath, '/');
#if defined(KGR_PLATFORM_WINDOWS)
        if (!base) {
            base = strrchr(filepath, '\\');
        }
#endif
        return base ? (base + 1) : filepath;
    }

    bool file_is_exists(const char *filepath)
    {
#if defined(KGR_PLATFORM_LINUX)
        return access(filepath, F_OK) == 0;
#elif defined(KGR_PLATFORM_WINDOWS)
        return _access(filepath, F_OK) != -1;
#endif
    }

    bool path_is_exists(const char *directory)
    {
#if defined(KGR_PLATFORM_LINUX)
        DIR *dir = opendir(directory);
        if (dir != nullptr) {
            closedir(dir);
            return true;
        }
#elif defined(KGR_PLATFORM_WINDOWS)
        return (access(directory, F_OK) != -1);
#endif
    }

    void create_directory(const char *directory)
    {
#if defined(KGR_PLATFORM_LINUX)
        DIR *dir = opendir(directory);
        if (dir == NULL) {
            mkdir(directory, S_IRWXU);
        } else {
            closedir(dir);
        }
#elif defined(KGR_PLATFORM_WINDOWS)
        if (_access(directory, 0) == -1) {
            CreateDirectoryA(directory, NULL);
        }
#endif
    }

    bool remove_directory(const char *directory)
    {
        if (path_is_exists(directory)) {
#if defined(KGR_PLATFORM_LINUX)
            if (rmdir(directory) != 0) {
                return true;
            }
#elif defined(KGR_PLATFORM_WINDOWS)

#endif
        }
        return false;
    }

    bool remove_file(const char *filepath)
    {
#if defined(KGR_PLATFORM_LINUX)
        if (file_is_exists(filepath)) {
            if (::remove(filepath) != 0) {
                return false;
            }
        }
#elif defined(KGR_PLATFORM_WINDOWS)
        return false;
#endif
        return true;
    }

} // namespace kgr