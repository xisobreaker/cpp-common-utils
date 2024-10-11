#include "xiso_nettools.h"
#include "xiso_types.h"

#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <endian.h>
#include <sys/socket.h>

namespace xiso {
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

const struct sockaddr *sockaddr_cast(const struct sockaddr_in6 *addr)
{
    return static_cast<const struct sockaddr *>(implicit_cast<const void *>(addr));
}

struct sockaddr *sockaddr_cast(struct sockaddr_in6 *addr)
{
    return static_cast<struct sockaddr *>(implicit_cast<void *>(addr));
}

const struct sockaddr *sockaddr_cast(const struct sockaddr_in *addr)
{
    return static_cast<const struct sockaddr *>(implicit_cast<const void *>(addr));
}

const struct sockaddr_in *sockaddr_in_cast(const struct sockaddr *addr)
{
    return static_cast<const struct sockaddr_in *>(implicit_cast<const void *>(addr));
}

const struct sockaddr_in6 *sockaddr_in6_cast(const struct sockaddr *addr)
{
    return static_cast<const struct sockaddr_in6 *>(implicit_cast<const void *>(addr));
}

void sockaddr_to_ip(char *buf, size_t size, const struct sockaddr *addr)
{
    if (addr->sa_family == AF_INET) {
        assert(size >= INET_ADDRSTRLEN);
        const struct sockaddr_in *addr4 = sockaddr_in_cast(addr);
        ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
    } else if (addr->sa_family == AF_INET6) {
        assert(size >= INET6_ADDRSTRLEN);
        const struct sockaddr_in6 *addr6 = sockaddr_in6_cast(addr);
        ::inet_ntop(AF_INET6, &addr6->sin6_addr, buf, static_cast<socklen_t>(size));
    }
}

void sockaddr_to_ipport(char *buf, size_t size, const struct sockaddr *addr)
{
    if (addr->sa_family == AF_INET6) {
        buf[0] = '[';
        sockaddr_to_ip(buf + 1, size - 1, addr);
        size_t                     end   = ::strlen(buf);
        const struct sockaddr_in6 *addr6 = sockaddr_in6_cast(addr);
        uint16_t                   port  = ntohs(addr6->sin6_port);
        snprintf(buf + end, size - end, "]:%u", port);
        return;
    }
    sockaddr_to_ip(buf, size, addr);
    size_t                    end   = ::strlen(buf);
    const struct sockaddr_in *addr4 = sockaddr_in_cast(addr);
    uint16_t                  port  = ntohs(addr4->sin_port);
    snprintf(buf + end, size - end, ":%u", port);
}

} // namespace xiso