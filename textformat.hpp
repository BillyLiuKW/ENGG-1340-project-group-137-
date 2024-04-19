#ifndef TEXTFORMAT_HPP
#define TEXTFORMAT_HPP

#include <iostream>
#include <map>
#include <string>


const std::map <std::string, std::string> formatMap = {
    {"reset", "\033[0m"},
    {"bold", "\033[1m"},
    {"italics", "\033[3m"},
    {"underline", "\033[4m"},
    {"invert", "\033[7m"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"purple", "\033[35m"},
    {"cyan", "\033[36m"}
};

#endif
