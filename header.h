#pragma once
#include <bits/stdc++.h>
#include "json.hpp"
#include <string>
class ContractM;
class AccessoryM;
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

inline int caesarNormalizeShift(int shift){
    shift %= 26;
    if(shift < 0){
        shift += 26;
    }
    return shift;
}

inline char caesarEncodeChar(char ch, int shift){
    shift = caesarNormalizeShift(shift);

    if(ch >= 'A' && ch <= 'Z'){
        return static_cast<char>((ch - 'A' + shift) % 26 + 'A');
    }
    if(ch >= 'a' && ch <= 'z'){
        return static_cast<char>((ch - 'a' + shift) % 26 + 'a');
    }
    return ch;
}

inline char caesarDecodeChar(char ch, int shift){
    shift = caesarNormalizeShift(shift);
    return caesarEncodeChar(ch, shift == 0 ? 0 : 26 - shift);
}

void startmenu(ContractM& manager, AccessoryM& accessoryManager);
void play();
void levelselect();
void setting();