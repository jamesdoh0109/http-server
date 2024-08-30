#include <sstream>
#include "http.h"
#include "http_response.h"

/*************************************************
 * Set the response status code.
 * 
 * @param: statusCode value
 *************************************************/
void HttpResponse::setStatusCode(HttpStatusCode statusCode)
{
    this->statusCode = statusCode;
}

/*************************************************
 * Set the response content and content type.
 * 
 * @param: content value
 * @param: content type
 *************************************************/
void HttpResponse::setContent(std::string content, std::string contentType)
{
    this->content = content;
    this->contentType = contentType;
}

/****************************************************
 * Get the raw string representation of the response
 * 
 * @param: content value
 * @param: content type
 *
 * @returns raw string
 ***************************************************/
const std::string HttpResponse::getRawResponseString(void)
{
    std::ostringstream outputStream;
    outputStream << "HTTP/1.1 " << static_cast<int>(statusCode) << " ";
    outputStream << toString(statusCode) << "\r\n";
    outputStream << "Content-Type: " << contentType << "\r\n";
    outputStream << "Content-Length: " << content.length() << "\r\n\r\n";
    outputStream << content;
    
    return outputStream.str();
}

/****************************************************
 * Construct OK response with given content and 
 * content type 
 * 
 * @param: content value
 * @param: content type
 *
 * @returns HttpResponse
 ***************************************************/
HttpResponse HttpResponse::getOkResponse(std::string content, std::string contentType)
{
    HttpResponse response;
    response.setContent(content, contentType);

    return response;
}