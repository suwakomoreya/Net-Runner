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