#pragma once
#include <bits/stdc++.h>
class Accessory{
    public:
    int id;
    std::string name;
    std::string description;
    int price;
    int bonuslives;
    int bonustime;
    double credmultiplier;
    int rawcredboost;

};
class AccessoryM{
    public:
    std::vector<Accessory> itemlist;
    std::unordered_map<int,bool> ownedaccessories;
    
    enum class Purchaseresult{
        Success,
        Notfound,
        Alreadyowned,
        Toopoor,
        Savefail
    };
    bool loaditemlist();
    bool loadplayerlist(int& streetcred);
    bool saveplayerdataAC(int streetcred);
    bool ownsaccessory(int id) const;
    Purchaseresult purchaseaccessory(int id, int& streetcred);
    int getbonuslives() const;
    int getbonustime() const;
    double getcredmult() const;
    int getrawcboost() const;
};