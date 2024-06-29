#include "kgr_filesystem.h"

#include "config/platform.h"
#include "kgr_file.h"

#include <cstring>

#if defined(KGR_PLATFORM_LINUX)
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
#elif defined(KGR_PLATFORM_WINDOWS)
    #include <Windows.h>
    #include <io.h>
#endif

namespace kgr {
    namespace filesystem {

        void create_directory_recurse(const std::string &directory)
        {
            unsigned long long pos = directory.rfind('/');
#if defined(KGR_PLATFORM_WINDOWS)
            if (pos == std::string::npos) {
                pos = directory.rfind('\\');
            }
#endif
            if (pos != std::string::npos && pos != 0) {
                create_directory_recurse(directory.substr(0, pos));
            }
            kgr::create_directory(directory.c_str());
        }

        bool remove_directory_recurse(const char *directory)
        {
#if defined(KGR_PLATFORM_LINUX)
            DIR *dir = opendir(directory);
            if (dir == nullptr)
                return false;
            dirent *entry;
            while ((entry = readdir(dir)) != nullptr) {
                // 跳过当前目录和父目录
                if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
                    continue;
                }

                std::string filepath = std::string(directory) + "/" + entry->d_name;
                if (entry->d_type == DT_DIR) {
                    if (!remove_directory_recurse(filepath.c_str())) {
                        closedir(dir);
                        return false;
                    }
                } else {
                    if (remove(filepath.c_str()) != 0) {
                        closedir(dir);
                        return false;
                    }
                }
            }

            closedir(dir);
            if (rmdir(directory) != 0) {
                return false;
            }
            return true;
#elif defined(KGR_PLATFORM_WINDOWS)
            char tmp_filepath[2048] = {0};
            sprintf_s(tmp_filepath, "%s\\*.*", directory);
            WIN32_FIND_DATAA fileData;
            HANDLE           hFile = FindFirstFileA(tmp_filepath, &fileData);
            if (hFile == INVALID_HANDLE_VALUE) {
                return false;
            }

            do {
                if (strcmp(".", fileData.cFileName) == 0 || strcmp("..", fileData.cFileName) == 0) {
                    continue;
                } else if (fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    char filepath[2048] = {0};
                    sprintf_s(filepath, "%s\\%s", directory, fileData.cFileName);
                    if (!remove_directory_recurse(directory)) {
                        return false;
                    }
                } else {
                    char filepath[2048] = {0};
                    sprintf_s(filepath, "%s\\%s", directory, fileData.cFileName);
                    if (remove(filepath) != 0) {
                        return false;
                    }
                }
            } while (FindNextFileA(hFile, &fileData));

            if (!RemoveDirectoryA(directory)) {
                return false;
            }
            return true;
#endif
        }

    } // namespace filesystem
} // namespace kgr