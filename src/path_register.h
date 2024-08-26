#ifndef PATH_REGISTER_H
#define PATH_REGISTER_H

#include <string>
#include <vector>
#include "http.h"
#include "http_request.h"
#include "http_response.h"
#include "static_content_register.h"

// handle function pointer type
using HandlerType = HttpResponse(HttpRequest &, StaticContentRegister &);

struct PathEntry
{
    std::vector<std::string> pathParts;
    HttpMethod method;
    HandlerType *handler;

    /******************************************************
     * Parameterized contructor to initialize data members
     *
     * @param: pathParts - Splited list of parts by '/'
     * @param: method - Http request method
     * @param: handler - Pointer to handler method
     ******************************************************/
    PathEntry(std::vector<std::string> pathParts, HttpMethod method, HandlerType *handler) : pathParts(pathParts),
                                                                                             method(method),
                                                                                             handler(handler) {}
};

class PathRegister
{
    std::vector<PathEntry> pathEntries; // List of path entries

    /**************************************************
     * Find the index of path entry that matches with
     * given path.
     *
     * @param: path - resource path in http request
     * @param: method - Http request method
     *
     * @returns index of the matched path entry.
     **************************************************/
    int findPath(const std::string &path, const HttpMethod &method);

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
    bool isPathMatched(const PathEntry &pathEntry, const std::vector<std::string> &pathParts);

public:
    /*************************************************
     * Default contructor to initilize object members
     *************************************************/
    PathRegister() {}

    /*****************************************************
     * Add given path into Path entries along with
     * http request method and corresponding handler.
     *
     * @param: path - resource path
     * @param: method - Path entry of http request method
     * @param: handler - Pointer to handler method
     *****************************************************/
    void addPath(const std::string &path, const HttpMethod &method, HandlerType handler);

    /*****************************************************
     * Get corresponding handler to given path and http
     * request method.
     *
     * @param: path - Resource path
     * @param: method - Http request method
     *
     * @returns Pointer to the handler method.
     ******************************************************/
    HandlerType *getHandler(const std::string &path, const HttpMethod &method);
};

#endif