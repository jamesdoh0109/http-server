#include <string>
#include "http.h"

std::string toString(const HttpStatusCode &statusCode)
{
  switch (statusCode)
  {
  case HttpStatusCode::OK:
    return "OK";

  case HttpStatusCode::ACCEPTED:
    return "Accepted";

  case HttpStatusCode::BAD_REQUEST:
    return "Bad Request";

  case HttpStatusCode::UNAUTHORIZED:
    return "Unauthorized";

  case HttpStatusCode::NOT_FOUND:
    return "Not Found";

  case HttpStatusCode::INTERNAL_SERVER_ERROR:
    return "Internal Server Error";

  default:
    return std::string();
  }
}

HttpMethod toHttpMethod(const std::string &methodStr)
{
  if (methodStr == "GET")
  {
    return HttpMethod::GET;
  }
  else if (methodStr == "POST")
  {
    return HttpMethod::GET;
  }
  else if (methodStr == "PATCH")
  {
    return HttpMethod::PATCH;
  }

  return HttpMethod::DELETE;
}