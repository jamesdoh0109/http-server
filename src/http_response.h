#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include "http.h"

class HttpResponse {
    HttpStatusCode statusCode;   // Response status code
    std::string contentType;     // Response content type
    std::string content;         // Response content

public:
    /*************************************************
     * Default contructor to initilize object members
     * ResponseCode: Ok
     * ContentType: "text/html"
     * Content: "" 
     *************************************************/
    HttpResponse(): statusCode(HttpStatusCode::OK), contentType("text/html"), content("") {}

    /*************************************************
     * Set the response status code.
     * 
     * @param: statusCode value
     *************************************************/
    void setStatusCode(HttpStatusCode statusCode);

    /*************************************************
     * Set the response content and content type.
     * 
     * @param: content value
     * @param: content type
     *************************************************/
    void setContent(std::string content, std::string contentType);

    /****************************************************
     * Get the raw string representation of the response
     * 
     * @param: content value
     * @param: content type
     *
     * @returns raw string
     ***************************************************/
    const std::string getRawResponseString(void);

    /****************************************************
     * Construct OK response with given content and 
     * content type 
     * 
     * @param: content value
     * @param: content type
     *
     * @returns HttpResponse
     ***************************************************/
    static HttpResponse getOkResponse(std::string content, std::string contentType);
};

#endif // HTTP_REQUEST_H