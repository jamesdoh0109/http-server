/*==========================================================
 * PathRegistry class implementation that holds all the
 * request path along with http request method and handler
 * method pointer.
 *==========================================================*/

#include <cstdio>
#include <string>
#include <vector>
#include "http.h"
#include "utility.h"
#include "http_response.h"
#include "http_request.h"
#include "path_register.h"

/**************************************************
 * Find the index of path entry that matches with
 * given path.
 *
 * @param: path - resource path in http request
 * @param: method - Http request method
 *
 * @returns index of the matched path entry.
 **************************************************/
int PathRegister::findPath(const std::string &path, const HttpMethod &method)
{
    std::vector<std::string> pathParts = split(path, '/');
    for (int i = 0, n = pathEntries.size(); i < n; i++)
    {
        if (pathEntries[i].method == method && isPathMatched(pathEntries[i], pathParts))
        {
            return i;
        }
    }

    return -1;
}

/**************************************************
 * To check path is matching or not with given
 * path entry in path register.
 *
 * @param: pathEntry - A path entry
 * @param: pathParts - Http request resource path
 *                     splited by '/'
 *
 * @returns true if path matched, else false.
 *************************************************/
bool PathRegister::isPathMatched(const PathEntry &pathEntry, const std::vector<std::string> &pathParts)
{
    if (pathEntry.pathParts.size() != pathParts.size())
    {
        return false;
    }

    for (int i = 0, n = pathParts.size(); i < n; i++)
    {
        if (!isParameter(pathEntry.pathParts[i]) && pathParts[i] != pathEntry.pathParts[i])
        {
            return false;
        }
    }

    return true;
}

/*****************************************************
 * Add given path into Path entries along with
 * http request method and corresponding handler.
 *
 * @param: path - resource path
 * @param: method - Path entry of http request method
 * @param: handler - Pointer to handler method
 *****************************************************/
void PathRegister::addPath(const std::string &path, const HttpMethod &method, HandlerType handler)
{
    pathEntries.push_back(PathEntry(split(path, '/'), method, handler));
}

/*****************************************************
 * Get corresponding handler to given path and http
 * request method.
 *
 * @param: path - Resource path
 * @param: method - Http request method
 *
 * @returns Pointer to the handler method.
 ******************************************************/
HandlerType *PathRegister::getHandler(const std::string &path, const HttpMethod &method)
{
    int index = findPath(path, method);
    if (index == -1)
    {
        return nullptr;
    }

    return pathEntries[index].handler;
}