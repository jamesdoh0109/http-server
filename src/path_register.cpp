#include <cstdio>
#include <string>
#include "http.h"
#include "http_response.h"
#include "http_request.h"
#include "path_register.h"

void PathRegister::addPath(std::string path,
                           HttpMethod method,
                           HandlerType handler)
{
    pathEntries.push_back(PathEntry(path, method, handler));
}

int PathRegister::findPath(std::string path, HttpMethod method)
{
    for (int i = 0, n = pathEntries.size(); i < n; i++)
    {
        if (pathEntries[i].method == method && pathEntries[i].path == path)
        {
            return i;
        }
    }

    return -1;
}

HandlerType *PathRegister::getHandler(std::string path, HttpMethod method)
{
    int index = findPath(path, method);
    if (index == -1)
    {
        return nullptr;
    }

    return pathEntries[index].handler;
}