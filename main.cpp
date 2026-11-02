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
#include "accessory.h"
void browseAccessories(AccessoryM& manager);
using json = nlohmann::json;
//libs
int streetcred = 30;
int selectedMid =0;
bool laststage = false, missionselected = false;


void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

void startmenu(ContractM& manager, AccessoryM& accessoryManager){
    std::vector<Contract>& contracts = manager.contracts;
    
    
    std::string menutext[] ={
        "Select a contract",
        "Browse available contracts",
        "Select gear",
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
        for(int i =0; i<count; i++){ //navigationals
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
                    manager.startContract(selectedMid,accessoryManager);
                    missionselected = false;
                    selectedMid =0;
                    
                }
                
                break;
                
            case 1: //contracts
                clearterm();
                manager.browseContract(streetcred);
                selected =0;
                break;
            case 2: //gear
                browseAccessories(accessoryManager);
                break;
            
            case 3: //kill term
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
void cselect(){
    int selected=1;
}
/** void saveplayerdata(){
    std::ofstream file("data/playerdata.json");
    if(!file.is_open()){
        std::cout << "Can't save player data :(";
        return;
    }
    json data;
    data["streetcred"] = streetcred;
    file << data.dump(4);
    file.close();
} */
/** void loadplayerdata(){
    std::ifstream file("data/playerdata.json");
    if(!file.is_open()){
        streetcred = 10;
        saveplayerdata();
        return;
    }
    json data;
    file >> data;
    streetcred = data.value("streetcred", 10);
    file.close();
}
*/

bool ContractM::loadContract(){
    std::ifstream file("data/contracts.json");

    if(!file.is_open()){
        std::cerr << "Couldn't open contracts.json\n";
        return false;
    }

    try{
        json data;
        file >> data;

        if(!data.is_array()){
            throw std::runtime_error(
                "Contracts must be stored in an array"
            );
        }

        std::vector<Contract> loadedContracts;

        for(const auto& c : data){
            if(!c.is_object() ||
               !c.contains("cipher") ||
               !c["cipher"].is_object()){
                throw std::runtime_error(
                    "Invalid contract structure"
                );
            }

            Contract contract;

            contract.id = c.at("id").get<int>();
            contract.name = c.at("name").get<std::string>();
            contract.description =
                c.at("description").get<std::string>();
            contract.difficulty =
                c.at("difficulty").get<std::string>();
            contract.requiredcred =
                c.at("required_cred").get<int>();
            contract.rewardcred =
                c.at("reward_cred").get<int>();
            contract.completed = c.value("completed", false);

            contract.cipherType =
                c["cipher"].at("type").get<std::string>();
            contract.encmessage =
                c["cipher"].at("encrypted_message").get<std::string>();
            contract.shift =
                c["cipher"].at("shift").get<int>();

            if(contract.requiredcred < 0 ||
               contract.rewardcred < 0 ||
               contract.shift < 0 || contract.shift > 25){
                throw std::runtime_error(
                    "Invalid contract values"
                );
            }

            loadedContracts.push_back(contract);
        }

        contracts = std::move(loadedContracts);
        return true;
    }
    catch(const std::exception& e){
        std::cerr << "Invalid contracts.json: "
                  << e.what() << '\n';
        return false;
    }
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
                std::cout << Color::white << "      " << "Status: ";
                if(c.completed == true){
                    std::cout << Color::green << "Completed" << Color::reset << std::endl;
                }
                else
                    std::cout << Color::red << "Incomplete" << Color::reset << std::endl;

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
void ContractM::startContract(int id, AccessoryM& accessoryManager){
    auto It = std::find_if(
        contracts.begin(), contracts.end(),
        [id](const Contract& c){
            return c.id == id;
        }
    );

    if(It == contracts.end()){
        std::cout << "Contract id can't be found: " << id << "\n";
        _getch();
        return;
    }

    Contract& c = *It;

    int timelimit = 30;

    long long totallives = 3LL + accessoryManager.getbonuslives();
    int lives = static_cast<int>(std::min<long long>(
        totallives, std::numeric_limits<int>::max()
    ));

    std::string answer = c.encmessage;
    std::string userans;

    // Decode Caesar cipher (letters only, keeps case and punctuation)
    for(char& ch : answer){
        ch = caesarDecodeChar(ch, c.shift);
    }

    auto winscreen = [&](){
        std::cout << "=================================" << std::endl;
        std::cout << "Contract '" << c.name << "' completed." << std::endl;
        std::cout << "Streetcred: " << streetcred;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        double multiplier = accessoryManager.getcredmult();
        double rewardvalue = c.rewardcred * multiplier;

        long long reward = 0;
        if(std::isfinite(multiplier) && std::isfinite(rewardvalue) &&
           rewardvalue > 0){
            if(rewardvalue >= static_cast<double>(
                   std::numeric_limits<int>::max())){
                reward = std::numeric_limits<int>::max();
            }
            else{
                reward = static_cast<long long>(std::round(rewardvalue));
            }
        }
        reward += accessoryManager.getrawcboost();

        long long newcred = static_cast<long long>(streetcred) + reward;
        newcred = std::max(0LL, std::min<long long>(
            newcred, std::numeric_limits<int>::max()
        ));

        for(long long i = streetcred; i < newcred; i++){
            std::cout << "\r\033[2K" << std::flush;
            std::cout << "Streetcred: " << i + 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        streetcred = static_cast<int>(newcred);
        c.completed = true;

        savecontractprogress();
        accessoryManager.saveplayerdataAC(streetcred);

        _getch();
        std::cout << "\033[?25h";
    };

    auto failscreen = [&](){
        clearterm();

        std::cout << Color::red << "Contract failed" << std::endl;
        std::cout << Color::reset << "Streetcred: " << streetcred;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        int oldcred = streetcred;
        int newcred = std::max(0, streetcred - 10);

        for(int i = oldcred; i > newcred; i--){
            std::cout << "\r\033[2K" << std::flush;
            std::cout << "Streetcred: " << i - 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        streetcred = newcred;
        accessoryManager.saveplayerdataAC(streetcred);

        _getch();
        std::cout << "\033[?25h";
    };

    auto initgraphic = [&](){
        if(c.difficulty == "Easy"){
            timelimit = 60;
        }
        else if(c.difficulty == "Medium"){
            timelimit = 45;
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

        for(int i = 0; i < 3; i++){
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::cout << Color::reset << Color::green
                  << std::endl << "Ready!" << Color::reset << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "Decipher type: Caesar (Every letter is shifted to the right alphabetically by X amount)" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        std::cout << "Press anything to start Caesar Decipher" << std::endl;
        _getch();

        clearterm();
    };

    initgraphic();

    long long totaltime = static_cast<long long>(timelimit)
        + accessoryManager.getbonustime();
    timelimit = static_cast<int>(std::min<long long>(
        totaltime, std::numeric_limits<int>::max()
    ));

    for(int i = 3; i > 0; i--){
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        clearterm();
    }

    auto starttime = std::chrono::steady_clock::now();

    std::cout << "\033[?25l";
    std::cout << "Time: " << timelimit << " seconds\n";
    std::cout << "Encrypted Message (USE CAPS): " << c.encmessage << "\n";
    std::cout << "Remaining lives: " << lives << "\n";
    std::cout << "Input: " << std::flush;
    while(true){
        auto now = std::chrono::steady_clock::now();

        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - starttime
        ).count();

        int remaining = timelimit - elapsed;

        if(remaining <= 0){
            failscreen();
            return;
        }

        std::cout << "\r\033[4A";
        std::cout << "\033[2KTime: " << remaining << " seconds\n";
        std::cout << "\033[2KEncrypted Message (USE CAPS): " << c.encmessage << "\n";
        std::cout << "\033[2KRemaining lives: " << lives << "\n";
        std::cout << "\033[2KInput: " << userans << std::flush;

        if(_kbhit()){
            int key = _getch();

            if(key == 0 || key == 224){
                _getch();
                continue;
            }

            if(key == '\r'){
                if(userans == answer){
                    clearterm();
                    winscreen();
                    return;
                }

                lives--;
                userans.clear();

                if(lives <= 0){
                    failscreen();
                    return;
                }
            }
            else if(key == '\b'){
                if(!userans.empty()){
                    userans.pop_back();
                }
            }
            else if(std::isalnum(static_cast<unsigned char>(key))){
                if(userans.size() < answer.size()){
                    userans += static_cast<char>(key);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void ContractM::savecontractprogress(){
    try{
        std::ifstream in("data/contracts.json");
        if(!in.is_open()){
            std::cout << "Could not read contracts.json";
            return;
        }
        json data;
        in >> data;
        in.close();

        if(!data.is_array()){
            std::cout << "Could not save contract progress";
            return;
        }

        for(auto& entry:data){
            if(!entry.is_object()){
                continue;
            }
            int id = entry.value("id",-1);
                auto it = std::find_if(contracts.begin(),contracts.end(),[id](const Contract& c){
                    return c.id == id;
                }
            );
            if(it != contracts.end()){
                entry["completed"] = it->completed;
            }
        }
        std::ofstream out("data/contracts.json");
        if(!out.is_open()){
            std::cout << "Could not write to contracts.json";
            return;
        }
        out << data.dump(4);
        out.close();
    }
    catch(const std::exception& e){
        std::cout << "Could not save contract progress: "
                  << e.what() << std::endl;
    }
}

void browseAccessories(AccessoryM& manager){
    if(manager.itemlist.empty()){
        std::cout << "Nothin in shop";
        _getch();
        return;
    }
    int selected=0;
    int count = manager.itemlist.size();
    while(true){
        clearterm();
        std::cout << "============================" << std::endl;
        std::cout << "    UPGRADES/ACCESSORIES"  << std::endl;
        std::cout << "----------------------------" << std::endl;
        std::cout << "Streetcred: " << streetcred << std::endl;
        for(int i=0;i<count;i++){
            const Accessory& item = manager.itemlist[i];
            std::cout << (i == selected ? "> ": " ");
            std::cout << item.name;
            if(manager.ownsaccessory(item.id)){
                std::cout << " [Owned]";
            }
            else{
                std::cout << " [" << item.price << " SC]";
            }
            std::cout << std::endl;
            if(i ==selected){
                std::cout << "  " << item.description << std::endl;
            }
        }
        std::cout << "ESC: Return" << std::endl;
        int key = _getch();
        if(key==0 || key == 224){
            key = _getch();
        }
        switch(key){
            case 72:
                selected--;
                if(selected<0){
                    selected = count-1;

                }
                break;
            case 80:
                selected++;
                if(selected>=count){
                    selected =0;
                }
                break;
            case 13:{
                auto result = manager.purchaseaccessory(manager.itemlist[selected].id,streetcred);
                clearterm();
                switch(result){
                    case AccessoryM::Purchaseresult::Success:
                        std::cout << "Purchased";
                        break;
                    case AccessoryM::Purchaseresult::Alreadyowned:
                        std::cout << "Already owned";
                        break;
                    case AccessoryM::Purchaseresult::Toopoor:
                        std::cout << "You're too POOR!";
                        break;
                    case AccessoryM::Purchaseresult::Notfound:
                        std::cout << "No accessory???";
                        break;
                    case AccessoryM::Purchaseresult::Savefail:
                        std::cout << "Purchase was not saved";
                        break;
                } 
                _getch();
                break;
            }
            case 27: 
                return;
            }  
    }
}
bool AccessoryM::loaditemlist(){
    std::ifstream file("data/items.json");

    if(!file.is_open()){
        std::cerr << "Couldn't open items.json\n";
        return false;
    }

    try{
        json data;
        file >> data;

        if(!data.is_array()){
            std::cerr << "items.json must contain an array\n";
            return false;
        }

        std::vector<Accessory> loadedItems;

        for(const auto& item : data){
            if(!item.is_object()){
                throw std::runtime_error("Item must be an object");
            }

            Accessory a;

            a.id = item.at("id").get<int>();
            a.name = item.at("name").get<std::string>();
            a.description = item.at("Description").get<std::string>();
            a.price = item.at("price").get<int>();
            a.bonuslives = item.at("livebonus").get<int>();
            a.bonustime = item.at("timebonus").get<int>();
            a.credmultiplier = item.at("credmult").get<double>();
            a.rawcredboost = item.at("rawcredbonus").get<int>();

            if(a.price < 0 || a.bonuslives < 0 ||
               a.bonustime < 0 || a.rawcredboost < 0 ||
               !std::isfinite(a.credmultiplier) ||
               a.credmultiplier < 0){
                throw std::runtime_error("Invalid accessory values");
            }

            loadedItems.push_back(a);
        }

        itemlist = std::move(loadedItems);
        return true;
    }
    catch(const std::exception& e){
        std::cerr << "Invalid items.json: "
                  << e.what() << '\n';
        return false;
    }
}
bool AccessoryM::loadplayerlist(int& streetcred){
    std::ifstream file("data/playerdata.json");

   
    if(!file.is_open()){
        ownedaccessories.clear();

        for(const auto& item : itemlist){
            ownedaccessories[item.id] = false;
        }

        return saveplayerdataAC(streetcred);
    }

    try{
        json data;
        file >> data;

        if(!data.is_object()){
            throw std::runtime_error(
                "Player data must be a JSON object"
            );
        }

        int loadedStreetcred = streetcred;

        if(data.contains("streetcred")){
            if(!data["streetcred"].is_number_integer()){
                throw std::runtime_error(
                    "Streetcred must be an integer"
                );
            }

            long long value =
                data["streetcred"].get<long long>();

            if(value < 0 || value > INT_MAX){
                throw std::runtime_error(
                    "Streetcred is out of range"
                );
            }

            loadedStreetcred = static_cast<int>(value);
        }

        if(data.contains("items") &&
           !data["items"].is_object()){
            throw std::runtime_error(
                "Items must be a JSON object"
            );
        }

        std::unordered_map<int, bool> loadedOwnership;

        for(const auto& item : itemlist){
            std::string id = std::to_string(item.id);
            bool owned = false;

            if(data.contains("items") &&
               data["items"].contains(id)){

                if(!data["items"][id].is_boolean()){
                    throw std::runtime_error(
                        "Accessory ownership must be true or false"
                    );
                }

                owned = data["items"][id].get<bool>();
            }

            loadedOwnership[item.id] = owned;
        }

      
        streetcred = loadedStreetcred;
        ownedaccessories = std::move(loadedOwnership);

        return true;
    }
    catch(const std::exception& e){
        std::cerr << "Invalid playerdata.json: "
                  << e.what() << '\n';
        return false;
    }
}
bool AccessoryM::saveplayerdataAC(int streetcred){
    json data;
    data["streetcred"] = streetcred;
    data["items"] = json::object();
    for(const auto& item : itemlist){
        data["items"][std::to_string(item.id)]=ownsaccessory(item.id);

    }
    std::ofstream file("data/playerdata.json");
    if(!file.is_open()){
        std::cout << "Couldn't save playerdata.json";
        return false;
    }
    file << data.dump(4);
    file.close();
    return true;
}
bool AccessoryM::ownsaccessory(int id) const{
    auto it = ownedaccessories.find(id);
    return it != ownedaccessories.end() && it->second;

}
AccessoryM::Purchaseresult AccessoryM::purchaseaccessory(
    int id, int& streetcred
){
    auto it = std::find_if(
        itemlist.begin(),
        itemlist.end(),
        [id](const Accessory& a){
            return a.id == id;
        }
    );

    if(it == itemlist.end())
        return Purchaseresult::Notfound;

    if(ownsaccessory(id))
        return Purchaseresult::Alreadyowned;

    if(streetcred < it->price || it->price < 0)
        return Purchaseresult::Toopoor;

    streetcred -= it->price;
    ownedaccessories[id] = true;

    if(!saveplayerdataAC(streetcred)){
        streetcred += it->price;
        ownedaccessories[id] = false;
        return Purchaseresult::Savefail;
    }

    return Purchaseresult::Success;
}
int AccessoryM::getbonuslives() const{
    long long bonus = 0;
    for(const auto& item : itemlist){
        if(ownsaccessory(item.id)){
            bonus += item.bonuslives;
        }
    }
    return static_cast<int>(std::min<long long>(
        bonus, std::numeric_limits<int>::max()
    ));
}
int AccessoryM::getbonustime() const{
    long long bonus = 0;
    for(const auto& item :itemlist){
        if(ownsaccessory(item.id)){
            bonus += item.bonustime;

        }
    }
    return static_cast<int>(std::min<long long>(
        bonus, std::numeric_limits<int>::max()
    ));
}
double AccessoryM::getcredmult() const{
    double multiplier = 1.0;
    for(const auto& item : itemlist){
        if(ownsaccessory(item.id)){
            multiplier *= item.credmultiplier;
        }
    } 
    return multiplier;
}
int AccessoryM::getrawcboost() const{
    long long bonus = 0;
    for(const auto& item : itemlist){
        if(ownsaccessory(item.id)){
            bonus +=item.rawcredboost;
        }
    }
    return static_cast<int>(std::min<long long>(
        bonus, std::numeric_limits<int>::max()
    ));
}
int main(){
    
    ContractM manager;
    AccessoryM accessoryManager;
    accessoryManager.loaditemlist();
    accessoryManager.loadplayerlist(streetcred);
    manager.loadContract();
    // loadplayerdata();
    startmenu(manager, accessoryManager);
    return 0;
}