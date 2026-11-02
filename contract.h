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
class AccessoryM;
class ContractM{
    public:
        std::vector<Contract> contracts;
        bool loadContract();
        void browseContract(int streetcred);
        void startContract(int id, AccessoryM& accessoryManager);
        void savecontractprogress();
};
