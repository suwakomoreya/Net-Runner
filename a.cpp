#include "contract.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;
std::vector<Contract> contracts;

void loadContract(){
    std::ifstream file("data/contracts.json");

    json data;
    file >> data;
    for(auto&c : data){
        contracts.push_back({
            c["id"],
            c["name"],
            c["description"],
            c["difficulty"],
            c["requiredcred"],
            c["rewardcred"],
            
            c["cipherType"],
            c["encmessage"],
            c["shift"]
        });
    }
}

/** for(int i =0;i<contracts.size();i++){
        Contract& c= contracts[i];
        std::cout << "\n" << c.name << std::endl;
        std::cout << c.description << std::endl;
        if(streetcred>= c.requiredcred){
            std::cout << Color::green << "[READY]";
        }
        else{
            std::cout << Color::red << "[LOCKED] Requires " << Color::blue << c.requiredcred << Color::reset << " Streetcred";
        }
        std::cout << Color::reset << std::endl;

    } */