#include "xiso_system.h"

#if defined(XISO_PLATFORM_LINUX)
    #include <signal.h>

void signo_process(int signo, void (*handler)(int))
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(signo, &sa, nullptr);
}

bool execute_shell_command(std::string &result, const std::string &command)
{
    char buf[BUFSIZ + 1] = {0};

    FILE *fp = popen(command.c_str(), "r");
    if (fp == nullptr) {
        return false;
    }

    int len = 0;
    while ((len = fread(buf, 1, BUFSIZ, fp)) >= 0) {
        result.append(buf, buf + len);

        if (feof(fp))
            break;
    }
    return true;
}
#endif
