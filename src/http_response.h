#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include "http.h"

class HttpResponse {
    HttpStatusCode statusCode;
    std::string contentType;
    std::string content;

public:
    HttpResponse(): statusCode(HttpStatusCode::OK), contentType("text/html"), content("") {}
    void setStatusCode(HttpStatusCode statusCode);
    void setContent(std::string contentType, std::string content);
    const std::string getRawResponseString(void);

    // Static methods
    static HttpResponse getOkResponse(std::string content, std::string contentType);
};

#endif // HTTP_REQUEST_H