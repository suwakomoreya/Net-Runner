#include <bits/stdc++.h>
#include "json.hpp"
#include <string>
using json = nlohmann::json;
namespace Color {
    const std::string reset = "\033[0m";
    const std::string red = "\033[31m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string blue = "\033[34m";
    const std::string purple = "\033[35m";
    const std::string cyan = "\033[36m";
    const std::string white = "\033[37m";
    const std::string gray = "\033[90m";
    const std::string lgray = "\033[37m";

    const std::string bold = "\033[1m";
}
void startmenu();
void play();
void levelselect();
void setting();