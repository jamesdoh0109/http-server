#include <string>
#include <vector>
#include <sstream>
#include "utility.h"

/**************************************************
 * Check that given string is template parameter
 * or not. Template parameter starts with '{' and
 * ends with '}'
 *
 * @param: str - A string
 *
 * @returns true if given string is template
 *          parameter, else false.
 *************************************************/
bool isParameter(const std::string &str)
{
    return str.size() >= 2 && str[0] == '{' && str[str.size() - 1] == '}';
}

/*************************************************
 * Split the given string by given delimiter.
 *
 * @param: str
 * @param: delimiter - Delimitor or splitter char
 *
 * @returns A list of splitted substrings
 ************************************************/
std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream stringstream(str);
    std::string token;
    while (std::getline(stringstream, token, delimiter))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}