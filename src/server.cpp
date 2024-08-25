#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <pthread.h>
#include "server.h"
#include "client_info.h"
#include "http_request.h"
#include "http_response.h"
#include "path_register.h"

const std::string Server::LOCAL_HOST = "127.0.0.1";
const uint16_t Server::DEFAULT_PORT = 8081;
const uint16_t Server::MAX_THREADS = 100;
const int Server::BACKLOG_SIZE = 1000;
const int Server::MAX_BUFFER_SIZE = 4096;

struct ThreadArgs
{
    ClientInfo *clientInfo;
    PathRegister *pathRegister;
    StaticContentRegister *staticContentRegister;
};

Server::Server() : host(LOCAL_HOST),
                   port(DEFAULT_PORT),
                   threadCnt(0)
{
    createSocket();
    initAddress(LOCAL_HOST, DEFAULT_PORT);
}

Server::Server(std::string host, uint16_t port) : host(host),
                                                  port(port),
                                                  threadCnt(0)
{
    createSocket();
    initAddress(host, port);
}

void Server::createSocket()
{
    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw std::runtime_error("[Error]: Failed to create a TCP socket");
    }
}

void Server::initAddress(std::string host, uint16_t port)
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(host.c_str());
}

void Server::start()
{
    printf("Starting the web server...\n");
    // Bind to the set port and IP address:
    if (bind(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)))
    {
        throw std::runtime_error("[Error]: Couldn't bind to the port, Exiting...");
    }

    // Listen for incoming requests
    printf("Started the server successfully\n");
    printf("Server listening on %s:%u\n", host.c_str(), port);
    if (listen(socketFd, BACKLOG_SIZE) < 0)
    {
        throw std::runtime_error("[Error]: Error while listening, Exiting...");
    }

    listenClientRequests();
}

void Server::listenClientRequests()
{
    while (true)
    {
        // Accept an incoming connection
        ClientInfo *clientInfo = new ClientInfo();
        clientInfo->clientSock = accept(socketFd, (struct sockaddr *)&clientInfo->clientAddr, &clientInfo->len);
        if (clientInfo->clientSock < 0)
        {
            printf("Error in accpting connection, dropping it\n");
            delete clientInfo;
            continue;
        }

        // Create a thread to handle the request
        ThreadArgs *threadArgs = new ThreadArgs();
        threadArgs->clientInfo = clientInfo;
        threadArgs->pathRegister = &pathRegister;
        threadArgs->staticContentRegister = &staticContentRegister;
        pthread_attr_t threadAttr;
        pthread_attr_init(&threadAttr);
        pthread_t tid;
        if (pthread_create(&tid, &threadAttr, handleRequest, (void *)threadArgs) != 0)
        {
            printf("[Error]: Thread creation failed... Skipping the request");
        }
    }
}

void *Server::handleRequest(void *arg)
{
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    ClientInfo *clientInfo = threadArgs->clientInfo;
    PathRegister *pathRegister = threadArgs->pathRegister;
    StaticContentRegister *staticContentRegister = threadArgs->staticContentRegister;
    printf("Received a connection request from %s\n", inet_ntoa(clientInfo->clientAddr.sin_addr));
    char rawRequestString[MAX_BUFFER_SIZE];
    int bytes_read = 0;
    while ((bytes_read = recv(clientInfo->clientSock, rawRequestString, MAX_BUFFER_SIZE, 0)) > 0)
    {
        rawRequestString[bytes_read] = '\0';

        printf("%s", rawRequestString);
        // Parse the request
        HttpRequest request = HttpRequest(rawRequestString, bytes_read);

        // Fetch handler to handle the request based on request path and http method
        HandlerType *handler =
            pathRegister->getHandler(request.getRequestPath(), request.getMethod());

        // If handler found, call the handler else construct 404 not found response
        HttpResponse response;
        if (handler)
        {
            response = handler(request, *staticContentRegister);
        }
        else if (staticContentRegister->isFileExist(request.getRequestPath()))
        {
            std::pair<std::string, std::string> fileData = staticContentRegister->getFileContent(request.getRequestPath());
            response = HttpResponse::getOkResponse(fileData.first, fileData.second);
        }
        else
        {
            response.setStatusCode(HttpStatusCode::NOT_FOUND);
            response.setContent("<h3>Page not found</h3>", "text/html");
        }

        std::string rawResponse = response.getRawResponseString();
        if (send(clientInfo->clientSock, rawResponse.c_str(), rawResponse.length(), 0) >= 0)
        {
            printf("Message sent: %s\n", rawResponse.c_str());
        }
        else
        {
            printf("[Error]: Unable to send response\n");
        }
    }

    if (bytes_read == 0)
    {
        printf("Client disconnected\n");
    }
    else
    {
        printf("[Error]: Recv error\n");
    }

    close(clientInfo->clientSock);
    delete clientInfo;
    return nullptr;
}

void Server::setPathRegister(PathRegister pathRegister)
{
    this->pathRegister = pathRegister;
}

void Server::setStaticContentRegister(StaticContentRegister staticContentRegister)
{
    this->staticContentRegister = staticContentRegister;
}