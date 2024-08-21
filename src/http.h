#ifndef HTTP_H
#define HTTP_H

// Http request methods
enum class HttpMethod
{
  GET,
  POST,
  PATCH,
  DELETE
};

// Http response status code
enum class HttpStatusCode
{
  OK = 200,
  ACCEPTED = 202,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  NOT_FOUND = 404,
  INTERNAL_SERVER_ERROR = 500
};

std::string toString(const HttpStatusCode &statusCode);
HttpMethod toHttpMethod(const std::string &methodStr);

#endif // HTTP_H