#pragma once

#include "CoinStore.h"
#include <algorithm>
#include <string>
#include <list>
#include <map>

namespace std {
    template<class _container, class _Ty> inline
    bool contains(_container _C, const _Ty& _Val)
    {
        return std::find(_C.begin(), _C.end(), _Val) != _C.end(); 
    }
}

namespace VendingMachines {

    enum class StockedItemType {
        Invalid, Cola, Chips, Candy
    };

    enum class ItemCost {
        Invalid = 0, Chips = 50, Candy = 65, Cola = 100
    };

    enum class MessageType {
        InsertCoin, ThankYou, InsufficientFunds, Amount, SoldOut
    };

    class VendingMachine {
    public:
        int InsertedAmount;
        std::list<Coin*> InsertedCoins;
        //std::list<Coin*> ReturnSlot;
        int ReturnSlot;
        std::map<StockedItemType, int> Stock;
        MessageType MessageType;
        StockedItemType RequestedItem;
        CoinStore ChangeBank;

        VendingMachine();

        Coin* InsertCoin(Coin*);
        void UpdateInsertedAmount(Coin*);
        int GetInsertedAmount();

        void MakeChange(int amountOfChange);
        void ReturnMoney();
        void ClearReturnSlot();

        int CountStockOf(StockedItemType);
        void AddStockOf(StockedItemType, int);
        void RemoveStockOf(StockedItemType, int);
        int GetCostOf(StockedItemType);

        void RequestItem(StockedItemType);
        void PutItemInFoodSlot(StockedItemType);

        bool CanMakeChange();

        std::string GetDisplay();
    };

}