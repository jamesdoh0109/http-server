#ifndef STATIC_CONTENT_REGISTER
#define STATIC_CONTENT_REGISTER

#include <utility>
#include <string>
#include <unordered_map>

class StaticContentRegister
{
    std::unordered_map<std::string, std::string> staticFilesMapping;
    void findAllFiles(std::string directory);
    std::string readFile(std::string filepath);
    std::string getContentType(std::string filepath);
    std::string getExtension(std::string filepath);

public:
    StaticContentRegister() {}
    StaticContentRegister(std::string directory);
    std::pair<std::string, std::string> getFileContent(std::string filepath);
    bool isFileExist(std::string filepath);
};

#endif