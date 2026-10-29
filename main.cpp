#include <bits/stdc++.h>
#include <string>
#include "json.hpp"
#include "header.h"
using json = nlohmann::json;
//libs
int scred;
bool laststage = false;

void startmenu(){
    int choice=0;
    auto menugraphic =[&choice](){
        std::cout << "==================================" << std::endl;
        std::cout << "" << std::endl;
        std::cin >> choice;
    };
    while(true){
        switch(choice){
            case 1: //start
                
            case 2: //diff

            case 3: //settings
            case 4: //last
                if(laststage == false)
                    break;
            default:

        }
    }
}
void play(){}

int main(){
    std::cout << "Start";
    startmenu();
    std::cout << "End";
    return 0;
}