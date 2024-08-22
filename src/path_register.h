#ifndef PATH_REGISTER_H
#define PATH_REGISTER_H

#include <string>
#include <vector>
#include "http.h"
#include "http_request.h"
#include "http_response.h"

// handle function pointer type
using HandlerType = HttpResponse(HttpRequest &);

struct PathEntry
{
    std::string path;
    HttpMethod method;
    HandlerType *handler;

    PathEntry(std::string path, HttpMethod method, HandlerType *handler) : path(path),
                                                                           method(method),
                                                                           handler(handler) {}
};

class PathRegister
{
    std::vector<PathEntry> pathEntries;
    int findPath(std::string path, HttpMethod method);

public:
    PathRegister() {}
    void addPath(std::string path, HttpMethod method, HandlerType handler);
    HandlerType *getHandler(std::string path, HttpMethod method);
};

#endif