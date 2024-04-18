#ifndef TEXTFORMAT_HPP
#define TEXTFORMAT_HPP

#include <iostream>
#include <map>
#include <string>


const std::map <std::string, std::string> formatMap = {
    {"reset", "\033[0m"},
    {"bold", "\033[1m"},
    {"red", "\033[31m"},
    {"yellow", "\033[33m"},
    {"cyan", "\033[36m"}
};

#endif
