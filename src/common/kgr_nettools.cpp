#include "kgr_nettools.h"

#include <arpa/inet.h>
#include <endian.h>

namespace kgr {
unsigned long long htonll(unsigned long long val)
{
    if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        unsigned long long high_order = htonl((unsigned int)(val & 0xFFFFFFFF));
        unsigned long long low_order  = htonl((unsigned int)(val >> 32));
        return (high_order << 32 | low_order);
    }
    return val;
}

unsigned long long ntohll(unsigned long long val)
{
    if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        unsigned long long high_order = ntohl((unsigned int)(val & 0xFFFFFFFF));
        unsigned long long low_order  = ntohl((unsigned int)(val >> 32));
        return (high_order << 32 | low_order);
    }
    return val;
}
} // namespace kgr