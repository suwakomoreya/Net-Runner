#include <bits/stdc++.h>
#include <string>
#include <conio.h>
#include "json.hpp"
#include "header.h"
using json = nlohmann::json;
//libs
int scred;
bool laststage = false, missionselected = false;
void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};
void startmenu(){
    int key = _getch();
    if(key == 0||key==224){
        key = _getch();
    }
    int selected = 0;
    int count;
    std::string menutext[] = {
        "Select a contract",
        "Browse available contracts",
        "Select gear",
        "View user data",
        "Exit terminal"
    };
    if(missionselected == true ){
        menutext[0] = "Start cipher";
    }
    auto menugraphic =[](){
        clearterm();
        std::cout << "==================================" << std::endl;
        std::cout << "Net Runner" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << Color::red << menutext[0] << std::endl;
        std::cout << Color::red << menutext[1] << std::endl;
        std::cout << Color::red << menutext[2] << std::endl;
        std::cout << Color::red << menutext[3] << std:endl;
        
    };
    auto runselection=[&selected](){ //menu
        if(selected ==0){// enter contract
            play();
        }
        if(selected ==1){

        }
        if(selected==2){

        }
    }; 
    while(true){ //menuinputs
        switch(key){
            case 72: 
                std::cout << "up";
                menugraphic();
                selected--;
                if(selected <0){
                    selected = count-1;
                }
                break;
            case 80:
                std::cout << "down";
                menugraphic();
                selected++;
                if(selected>=0){
                    selected = count+1;
                }
            case 27:
                clearterm();
                runselection();
                break;
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