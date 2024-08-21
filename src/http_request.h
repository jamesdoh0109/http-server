#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <string>
#include "http.h"

class HttpRequest
{
  HttpMethod method;
  std::string requestPath;
  std::map<std::string, std::string> requestHeader;

public:
  HttpRequest() : method(HttpMethod::GET), requestPath("") {}
  HttpRequest(char *message, int size);
  void parseRawRequestString(char *message, int size);
  HttpMethod getMethod(void);
  std::string getRequestPath(void);
};

#endif 