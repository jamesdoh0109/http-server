#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

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
bool isParameter(const std::string &str);

/*************************************************
 * Split the given string by given delimiter.
 *
 * @param: str
 * @param: delimiter - Delimitor or splitter char
 *
 * @returns A list of splitted substrings
 ************************************************/
std::vector<std::string> split(const std::string &str, char delimiter);

#endif // UTILITY_H