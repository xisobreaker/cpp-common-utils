#pragma once

#include <cstdint>
#include <netinet/in.h>

class UdpClient
{
public:
    UdpClient();
    UdpClient(uint16_t port);
    ~UdpClient();

public:
    int  send(const char *buf, int len, const char *ip, uint16_t port);
    int  send(const char *buf, int len, struct sockaddr *sa);
    int  recv(char *buf, int maxlen, struct sockaddr &sa);
    void close();

private:
    int sockfd_;
};