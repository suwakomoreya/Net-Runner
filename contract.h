#pragma once
#include <bits/stdc++.h>
class Contract{
    public: int id;
        std::string name;
        std::string description;
        std::string difficulty;
        int requiredcred;
        int rewardcred;

        std::string cipherType;
        std::string encmessage;
        int shift;
};
class ContractM{
    public:
        std::vector<Contract> contracts;
        void loadContract();
        void browseContract(int streetcred);
        void startContract(int index);
};