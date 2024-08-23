#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <sys/socket.h>

struct ClientInfo
{
    sockaddr_in clientAddr;
    int clientSock;
    int clientId;
    unsigned int len;

    ClientInfo() : len(sizeof(sockaddr_in))
    {
    }
};

#endif