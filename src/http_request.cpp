#include <string>
#include <sstream>
#include "http.h"
#include "http_request.h"

HttpRequest::HttpRequest(char *message, int size) : method(HttpMethod::GET), requestPath("")
{
  parseRawRequestString(message, size);
}

void HttpRequest::parseRawRequestString(char *message, int size)
{
  std::string methodStr;
  std::istringstream inputStream(message);
  inputStream >> methodStr >> requestPath;
  method = toHttpMethod(methodStr);
}

HttpMethod HttpRequest::getMethod(void)
{
  return method;
}

std::string HttpRequest::getRequestPath(void)
{
  return requestPath;
}