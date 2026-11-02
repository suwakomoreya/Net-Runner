#pragma once
#include <bits/stdc++.h>
class Contract{
    public: int id;
        std::string name;
        std::string description;
        std::string difficulty;
        int requiredcred;
        int rewardcred;
        bool completed;
        std::string cipherType;
        std::string encmessage;
        int shift;
};
class ContractM{
    public:
        std::vector<Contract> contracts;
        void loadContract();
        void browseContract(int streetcred);
        void startContract(int id);
        void savecontractprogress();
};
class Accessory{
    public:
    int id;
    std::string name;
    std::string description;
    int prices;
    int bonuslives;
    int bonustime;
    double credmultiplier;
    int rawcredbonus;
};
class AccessoryM{
    public:
    std::vector<Accessory> itemlist;
    std::unordered_map<int,bool> ownedAccessories;

    void loadItemList();
    bool ownsaccessory(int id);
    void purchaseAccessory(int id, int& streetcred);

    int gblives();
    int gbtime();
    double gcmult();
    int rcbonus();

};