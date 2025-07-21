#pragma once

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

    enum class CoinSize {
        Penny, Nickel, Dime, Quarter
    };

    enum class CoinWeight {
        Penny, Nickel, Dime, Quarter
    };

    enum class CoinValue {
        Invalid = 0,
        Penny = 1,
        Nickel = 5,
        Dime = 10,
        Quarter = 25
    };

    class Coin {
    public:
        Coin(CoinSize, CoinWeight);
        CoinWeight Weight;
        CoinSize Size;
        CoinValue Value;
    };

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