#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>
#include "json.hpp"
#include <filesystem>
#include "header.h"
#include "contract.h"
using json = nlohmann::json;
//libs
int streetcred = 10;
int selectedMid =0;
bool laststage = false, missionselected = false;


void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

void startmenu(ContractM& manager){
    std::vector<Contract>& contracts = manager.contracts;
    Contract& c = contracts[selectedMid];
    
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
        if(missionselected == true ){
        menutext[0] = "Start cipher";
    }
        auto it = std::find_if( //iterator
            contracts.begin(),contracts.end(),[](const Contract& c){
                return c.id == selectedMid;
            }
        );
        if(it!=contracts.end()){
            Contract&c = *it;
        }
        clearterm();
        
        std::cout << "==================================" << std::endl;
        std::cout << Color::bold << "Net Runner" << Color::reset << std::endl;
        std::cout << "selected: " << selected << std::endl; //del later
        std::cout << missionselected << "   " << selectedMid << std::endl;
        if(it!=contracts.end()){
            Contract& c = *it;
            std::cout << "Mission Selected: " << c.name << std::endl;
        }
        else{
            std::cout << "Mission Selected: Unemployed" << std::endl;
        } 
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Streetcred: " << streetcred << std::endl;
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
                if(missionselected == true){
                    clearterm();
                    manager.startContract(selectedMid);
                    break;
                }
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

void ContractM::loadContract(){
    std::ifstream file("data/contracts.json");
    if(!file.is_open()){
        std::cout << "couldnt open contracts.json";
        _getch();
        return;
    }

    json data;
    file >> data;

    for(auto& c : data){
        Contract contract;
        
        contract.id = c["id"];
        contract.name = c["name"];
        contract.description = c["description"];
        contract.difficulty = c["difficulty"];
        contract.requiredcred = c["required_cred"];
        contract.rewardcred = c["reward_cred"];

        contract.cipherType = c["cipher"]["type"];
        contract.encmessage = c["cipher"]["encrypted_message"];
        contract.shift = c["cipher"]["shift"];

        contracts.push_back(contract);
    }
    file.close();

    std::cout << "contracts loaded";
    _getch();
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
        auto check = [&](Contract& c){
            if(streetcred>=c.requiredcred){
                std::cout << Color::green << "[Ready]" << std::endl;
            }
            else{
                std::cout << Color::red << "[Locked]" << std::endl;
            }
        };
        for(int i =0; i<count;i++){
            Contract& c = contracts[i];

            std::string cdiff = c.difficulty == "Easy" ? Color::green : c.difficulty == "Medium" ? Color::yellow : Color::purple;

            if(i==selected){
                std::cout << Color::white << "> " << c.name << Color::reset;
                check(c);
                std::cout << Color::white << "      " << "Contract Info:" << c.description << Color::reset << std::endl;
                std::cout << Color::white << "      " << "Difficulty: "<< cdiff << c.difficulty << Color::reset << std::endl;
                std::cout << "      " << "Reward Credit: " << c.rewardcred << std::endl;
            }
            else{
                std::cout << Color::red << " " << c.name << Color::reset;
                check(c);
            }
        }
    };
    while(true){
        menugraphic();
        int key = _getch();
        if(key==0 || key == 224){
            key = _getch();
        }
    

        switch(key){
            case 72:
                selected--;
                if(selected < 0){
                    selected = count-1;

                }
                break;
            case 80:
                selected++;
                if(selected >= count){
                    selected = 0;

                }
                break;
            case 13:
                if(streetcred>=contracts[selected].requiredcred){
                    clearterm();
                    missionselected = true;
                    selectedMid = contracts[selected].id;
                    return;
                }
                else{
                    std::cout << "\n Required streetcred: " << Color::red << contracts[selected].requiredcred << Color::reset << std::endl;
                    std::cout << " Your streetcred: " << streetcred << std::endl;
                    _getch();
                }
            break;
            case 27: 
                return;
        }
    }
    _getch();
}
void ContractM::startContract(int id){
    Contract& c = contracts[selectedMid-1];
    int timelimit;
    std::string answer;
    auto answerenc = [&](){
        for(int i = 0;i< (c.encmessage).size(); i++){

        }
    };
    auto initgraphic = [&](){
        if(c.difficulty == "Easy"){
            timelimit = 90;
        }
        else if(c.difficulty == "Medium"){
            timelimit = 60;
        }
        else if(c.difficulty == "Hard"){
            timelimit = 45;
        }
        if(c.name == "Konpeki Plaza Heist"){
            timelimit = 50;
        }
        
        std::cout << "=========================================" << std::endl;
        std::cout << Color::red << "Contract: " << c.name << std::endl;
        std::cout << "Jacking in";
        for(int i=0;i<3;i++){
            std::cout << ".";
            std::cout << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << Color::reset << Color::green << std::endl << "Ready!" << Color::reset << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Decipher type: Caesar (Every letter is shifted to the right alphabetically by X amount)" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Press anything to start Caesar Decipher" << std::endl;
        _getch();     
    };
    auto starttime = std::chrono::steady_clock::now();


    initgraphic();
    
}
int main(){
    std::cout << "Loaded:" << std::filesystem::current_path() << std::endl;
    _getch();

    ContractM manager;
    manager.loadContract();
    std::cout << manager.contracts.size() << std::endl;
    _getch();
    startmenu(manager);
    return 0;
}