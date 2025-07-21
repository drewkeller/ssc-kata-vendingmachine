#include "CoinStore.h"

using namespace std;
using namespace VendingMachines;

CoinStore::CoinStore()
    : Coins( { {CoinValue::Quarter, 0}, {CoinValue::Dime, 0}, {CoinValue::Nickel, 0} })
    , Value(0)
{
}

void CoinStore::CalculateValue()
{
    Value = 25 * Coins[CoinValue::Quarter]
        + 10 * Coins[CoinValue::Dime]
        + 5 * Coins[CoinValue::Nickel];
}

void CoinStore::Fill(int quarters, int dimes, int nickels)
{
    Coins[CoinValue::Quarter] += quarters;
    Coins[CoinValue::Dime] += dimes;
    Coins[CoinValue::Nickel] += nickels;
    CalculateValue();
}

void CoinStore::Add(CoinValue coinValue, int qty)
{
    Coins[coinValue] += qty;
    Value += static_cast<int>(coinValue) * qty;
}

void CoinStore::Remove(CoinValue coinValue, int qty)
{
    Coins[coinValue] -= qty;
    Value -= static_cast<int>(coinValue) * qty;
}

void CoinStore::Clear()
{
    Coins[CoinValue::Quarter] = 0;
    Coins[CoinValue::Dime] = 0;
    Coins[CoinValue::Nickel] = 0;
    Value = 0;
}

bool CoinStore::Contains(CoinValue coinValue, int qty)
{
    return Coins[coinValue] >= qty;
}

bool CoinStore::CanMakeChange(int amountOfChange)
{
    int change = amountOfChange;

    for(auto coinValue : { CoinValue::Quarter, CoinValue::Dime, CoinValue::Nickel})
    {
        int value = static_cast<int>(coinValue);
        int qty = min(change / value, Coins[coinValue]);
        change -= qty * value;
    }

    return change == 0;
}

void CoinStore::MakeChange(int amountOfChange)
{
    int change = amountOfChange;

    for(auto coinValue : { CoinValue::Quarter, CoinValue::Dime, CoinValue::Nickel})
    {
        int value = static_cast<int>(coinValue);
        int qty = min(change / value, Coins[coinValue]);
        change -= qty * value;
        Remove(coinValue, qty);
    }
}
