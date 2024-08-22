#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include "static_content_register.h"

StaticContentRegister::StaticContentRegister(std::string directory)
{
    findAllFiles(directory);
}

std::pair<std::string, std::string> StaticContentRegister::getFileContent(std::string filepath)
{
    printf("Test: %s\n", filepath.c_str());
    filepath = "." + filepath;
    printf("Test: %s\n", filepath.c_str());
    auto fileMap = staticFilesMapping.find(filepath);
    if (fileMap == staticFilesMapping.end())
    {
        printf("Error: File not found");
        return {"", ""};
    }

    // Read file content
    std::string content = readFile(filepath);

    return {content, fileMap->second};
}

void StaticContentRegister::findAllFiles(std::string directory)
{
    std::filesystem::path directoryPath(directory);
    if (!std::filesystem::is_directory(directory))
    {
        printf("Error: Invalid directory\n");
        return;
    }

    for (const auto &directoryEntry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (directoryEntry.is_regular_file())
        {
            staticFilesMapping[directoryEntry.path()] = getContentType(directoryEntry.path());
            std::cout << directoryEntry.path() << std::endl;
        }
    }
}

std::string StaticContentRegister::readFile(std::string filepath)
{
    std::ifstream file(filepath);
    std::string content = "";
    std::string line;
    if (file.is_open())
    {
        while (!file.eof())
        {
            std::getline(file, line);
            content += line;
        }
    }

    return content;
}

std::string StaticContentRegister::getContentType(std::string filepath)
{
    std::string fileExtension = getExtension(filepath);
    if (fileExtension == "html")
    {
        return "text/html";
    }
    else if (fileExtension == "css")
    {
        return "text/css";
    }
    else if (fileExtension == "js")
    {
        return "text/js";
    }

    return "";
}

std::string StaticContentRegister::getExtension(std::string filepath)
{
    int index = -1;
    for (int i = filepath.length() - 1; i >= 0; i--)
    {
        if (filepath[i] == '.')
        {
            index = i + 1;
        }
    }

    if (index == -1)
    {
        return "";
    }

    return filepath.substr(index);
}

bool StaticContentRegister::isFileExist(std::string filepath)
{
    return staticFilesMapping.find("." + filepath) != staticFilesMapping.end();
}