#include "kgr_system.h"

#if defined(KGR_PLATFORM_LINUX)
void sig_process(int signo, void (*handler)(int))
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(signo, &sa, nullptr);
}
#endif
