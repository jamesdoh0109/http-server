#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client_info.h"
#include "path_register.h"
#include "static_content_register.h"

class Server
{
    // Static fields
    static const std::string LOCAL_HOST;
    static const uint16_t DEFAULT_PORT;
    static const uint16_t MAX_THREADS;
    static const int BACKLOG_SIZE;
    static const int MAX_BUFFER_SIZE;

    std::string host;                            // IP address of the host
    uint16_t port;                               // Port address
    sockaddr_in serverAddr;                      // Server address (IP address and port number)
    int socketFd;                                // Socket file descriptor
    int threadCnt;                               // Number of active threads
    PathRegister pathRegister;                   // Contains path and associated handler
    StaticContentRegister staticContentRegister; // Contains all the static files path along with content type

    void createSocket();
    void listenClientRequests();

    // Initialize server address
    void initAddress(std::string host, uint16_t port);
    static void *handleRequest(void *arg);

    std::string constructResponse();

public:
    Server(); // Create a server with localhost and default port.
    Server(std::string host, uint16_t port);
    void setPathRegister(PathRegister pathRegister);
    void setStaticContentRegister(StaticContentRegister staticContentRegister);
    void start();
};

#endif