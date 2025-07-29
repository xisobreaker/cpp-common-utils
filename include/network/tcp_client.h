#pragma once

#include <cstdint>

class TcpClient
{
public:
    TcpClient(const char *ip, uint16_t port);
    ~TcpClient();

public:
    int  connect();
    int  send(const char *buf, int len);
    int  recv(char *buf, int maxlen);
    void close();

private:
    int      sockfd_;
    char     ipaddr_[16];
    uint16_t port_;
};