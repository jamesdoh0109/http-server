#include <cstdio>
#include <fstream>
#include "server.h"
#include "path_register.h"
#include "static_content_register.h"

HttpResponse index(HttpRequest& request, StaticContentRegister& staticContentRegister)
{
    std::pair<std::string, std::string> fileContent = 
        staticContentRegister.getFileContent("/index.html");
    HttpResponse response;
    response.setStatusCode(HttpStatusCode::OK);
    response.setContent(fileContent.first, fileContent.second);
    
    return response;
}

HttpResponse about(HttpRequest& request, StaticContentRegister& staticContentRegister)
{
    std::string content = "<h1>This is a about page</h1>";
    HttpResponse response;
    response.setStatusCode(HttpStatusCode::OK);
    response.setContent("text/html", content);

    return response;
}

int main(int argc, char* argv[])
{
    // Find all the static files along with type
    StaticContentRegister staticContentRegister("./static_files");

    PathRegister pathRegister;
    pathRegister.addPath("/", HttpMethod::GET, index);
    pathRegister.addPath("/home", HttpMethod::GET, index);
    pathRegister.addPath("/about", HttpMethod::GET, about);
    
    Server server;
    server.setPathRegister(pathRegister);
    server.setStaticContentRegister(staticContentRegister);
    server.start();
    return 0;
}