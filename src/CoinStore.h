#pragma once

#include "Coin.h"
#include <algorithm>
#include <string>
#include <list>
#include <map>

namespace VendingMachines {

    class CoinStore {
    public:
        std::map<CoinValue, int> Coins;
        int Value;

        CoinStore(void);
        void CalculateValue();
        void Fill(int quarters, int dimes, int nickels);
        void Add(CoinValue, int);
        void Remove(CoinValue, int);
        void Clear();
        bool Contains(CoinValue, int);
        bool CanMakeChange(int amountOfChange);
        void MakeChange(int amountOfChange);
    };

}