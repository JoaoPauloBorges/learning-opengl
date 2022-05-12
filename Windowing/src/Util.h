#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

std::string loadfile(const std::string& path) {
    std::stringstream result;
    std::ifstream stream(path);

    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line))
        {
            result << line << '\n';
        }
        stream.close();
    }
    else
        std::cout << "Unable to open file\n";

    return result.str();
}
#endif