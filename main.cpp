#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "json.hpp"
#include "header.h"
using json = nlohmann::json;
//libs
int streetcred;
bool laststage = false, missionselected = true;

void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

void startmenu(){
    std::string menutext[] ={
        "Select a contract",
        "Browse available contracts",
        "Select gear",
        "View user data",
        "Exit terminal"
    };
    int selected = 0;
    int count = sizeof(menutext)/sizeof(menutext[0]);

    if(missionselected == true ){
        menutext[0] = "Start cipher";
    }
    auto menugraphic =[&menutext,&selected](){
        clearterm();
        
        std::cout << "==================================" << std::endl;
        std::cout << Color::bold << "Net Runner" << Color::reset << std::endl;
        std::cout << "selected: " << selected << std::endl; //del later
        std::cout << "----------------------------------" << std::endl;
        for(int i =0; i<5; i++){ //navigationals
            if(i==selected){
                std::cout << Color::white << ">. " << menutext[i] << Color::reset << std::endl;
            }
            else{
                std::cout << Color::red << menutext[i] << Color::reset << std::endl;
            }
        }
    };
    auto runselection=[&selected](){ //menu
        switch(selected){
            case 0: //select contract
                break;
            case 1: //contracts
                break;
            case 2: //gear
                break;
            case 3: //user data
                break;
            case 4: //kill term`
                std::exit(0);
        }
    };
    while(true){ //menuinputs
        menugraphic();
        int key = _getch();
        if(key == 0||key==224){
         key = _getch();
        }
        switch(key){
            case 72: 
                std::cout << "up";
                selected--;
                if(selected <0){
                    selected = count-1;
                }
                break;
            case 80:
                std::cout << "down";
                selected++;
                if(selected>=count){
                    selected = 0;
                }
                break;
            case 13: // enter
                clearterm();
                runselection();
                break;
        }
    }
}
void play(){}
void cselect(){
    int selected=1;

}
void userdata(){
    int selected=1;
}
int main(){
    std::cout << "Start";
    startmenu();
    std::cout << "End";
    return 0;
}