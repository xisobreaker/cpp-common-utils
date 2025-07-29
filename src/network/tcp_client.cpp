#include "tcp_client.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#ifndef INVALID_SOCKET
    #define INVALID_SOCKET (-1)
#endif

TcpClient::TcpClient(const char *ip, uint16_t port) : sockfd_(INVALID_SOCKET), port_(port)
{
    memset(ipaddr_, 0, 16);
    memcpy(ipaddr_, ip, strlen(ip));

    sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd_ == INVALID_SOCKET)
        throw std::runtime_error("Create udp socket failed.");
}

TcpClient::~TcpClient()
{
    this->close();
}

int TcpClient::connect()
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, ipaddr_, &sa.sin_addr);
    sa.sin_port = htons(port_);

    int ret = ::connect(sockfd_, (struct sockaddr *)&sa, sizeof(sa));
    if (ret == -1) {
        printf("Connect failed: %s", strerror(errno));
    }
    return ret;
}

int TcpClient::send(const char *buf, int len)
{
    if (sockfd_ == INVALID_SOCKET) {
        return -1;
    }

    int nbytes = 0;
    do {
        int ret = ::send(sockfd_, buf + nbytes, len - nbytes, MSG_NOSIGNAL);
        if (ret <= 0) {
            if (errno == EINTR)
                continue;

            printf("Send failed: %s", strerror(errno));
            return ret;
        }
        nbytes += ret;
    } while (nbytes != len);
    return nbytes;
}

int TcpClient::recv(char *buf, int maxlen)
{
    if (sockfd_ == INVALID_SOCKET) {
        return -1;
    }
    return ::recv(sockfd_, buf, maxlen, 0);
}

void TcpClient::close()
{
    if (sockfd_ != INVALID_SOCKET) {
        ::close(sockfd_);
        sockfd_ = INVALID_SOCKET;
    }
}
