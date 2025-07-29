#include "udp_client.h"

#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#ifndef INVALID_SOCKET
    #define INVALID_SOCKET (-1)
#endif

UdpClient::UdpClient() : UdpClient(0)
{
}

UdpClient::UdpClient(uint16_t port)
{
    sockfd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd_ == INVALID_SOCKET)
        throw std::runtime_error("Create udp socket failed.");

    if (port != 0) {
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family      = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port        = htons(port);
        if (::bind(sockfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            throw std::runtime_error("Bind udp address failed.");
        }
    }
}

UdpClient::~UdpClient()
{
    this->close();
}

int UdpClient::send(const char *buf, int len, const char *ip, uint16_t port)
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &sa.sin_addr);
    sa.sin_port = htons(port);

    return this->send(buf, len, (struct sockaddr *)&sa);
}

int UdpClient::send(const char *buf, int len, struct sockaddr *sa)
{
    if (sockfd_ == INVALID_SOCKET) {
        return -1;
    }

    return ::sendto(sockfd_, buf, len, 0, sa, sizeof(sockaddr));
}

int UdpClient::recv(char *buf, int maxlen, struct sockaddr &sa)
{
    if (sockfd_ == INVALID_SOCKET) {
        return -1;
    }

    socklen_t sz = sizeof(sa);
    return ::recvfrom(sockfd_, buf, maxlen, 0, &sa, &sz);
}

void UdpClient::close()
{
    if (sockfd_ != INVALID_SOCKET) {
        ::close(sockfd_);
        sockfd_ = INVALID_SOCKET;
    }
}
