#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "json.hpp"

#include "header.h"
#include "contract.h"
using json = nlohmann::json;
//libs
int streetcred = 120;
bool laststage = false, missionselected = true;

void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

void startmenu(ContractM& manager){
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
    auto menugraphic =[&](){
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
    auto runselection=[&](){ //menu
        switch(selected){
            case 0: //select contract
                break;
            case 1: //contracts
                clearterm();
                manager.browseContract(streetcred);
                break;
            case 2: //gear
                break;
            case 3: //user data
                break;
            case 4: //kill term
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
    ContractM manager;
    manager.loadContract();
    startmenu(manager);
    std::cout << "Start";
   
    std::cout << "End";
    return 0;
}

void ContractM::loadContract(){
    std::ifstream file("data/contracts.json");
    if(!file.is_open()){
        std::cout << "couldnt open contracts.json";
        return;
    }

    json data;
    file >> data;

    for(auto& c : data){
        Contract contract;
        
        contract.id = c["id"];
        contract.name = c["name"];
        contract.description = c["description"];
        contract.requiredcred = c["required_cred"];
        contract.rewardcred = c["reward_cred"];

        contract.cipherType = c["cipher"]["type"];
        contract.encmessage = c["cipher"]["encrypted_message"];
        contract.shift = c["cipher"]["shift"];

        contracts.push_back(contract);
    }
    file.close();
}
void ContractM::browseContract(int streetcred){ //NEED to fix this. currently cant find contracts. need to load contract maybe?
    if(contracts.empty()){
        std::cout << "no employment";
        _getch();
        return;
    }
    int selected =0;
    int count = contracts.size();
    
    auto menugraphic = [&](){
        clearterm();

        std::cout << "==================================" << std::endl;
        std::cout << Color::bold <<"Contracts" << Color::reset << std::endl;
        std::cout << "----------------------------------" << std::endl;

        for(int i =0; i<count;i++){
            Contract& c = contracts[i];
            if(i==selected){
                std::cout << Color::white << "> " << c.name << Color::reset << std::endl;
                std::cout << Color::white << "  " << c.description << Color::reset << std::endl;
            }
            else{
                std::cout << Color::red << " " << c.name << Color::reset;
            }
            if(streetcred>=c.requiredcred){
                std::cout << Color::green << "[Ready]";
            }
            else{
                std::cout << Color::red << "[Locked]";
            }
        }
    };

    for(int i =0;i<contracts.size();i++){
        Contract& c= contracts[i];
        std::cout << "\n" << c.name << std::endl;
        std::cout << c.description << std::endl;
        if(streetcred>= c.requiredcred){
            std::cout << Color::green << "[READY]";
        }
        else{
            std::cout << Color::red << "[LOCKED] Requires" << c.requiredcred << " Streetcred";
        }
        std::cout << Color::reset << std::endl;

    }
}