#include "VendingMachine.h"
#include <iostream>
#include <format>

using namespace std;
using namespace VendingMachines;

Coin::Coin(CoinSize size, CoinWeight weight)
: Weight(weight)
, Size(size)
, Value(CoinValue::Invalid)
{

}

VendingMachine::VendingMachine()
: InsertedAmount(0)
, InsertedCoins()
, ReturnSlot()
, Stock()
, MessageType(MessageType::InsertCoin)
, RequestedItem(StockedItemType::Invalid)
, ChangeBank()
{
}

Coin* VendingMachine::InsertCoin(Coin* coin)
{
    coin->Value =  
        (coin->Size == CoinSize::Penny && coin->Weight == CoinWeight::Penny) ? CoinValue::Penny
        : (coin->Size == CoinSize::Nickel && coin->Weight == CoinWeight::Nickel) ? CoinValue::Nickel
        : (coin->Size == CoinSize::Dime && coin->Weight == CoinWeight::Dime) ? CoinValue::Dime
        : (coin->Size == CoinSize::Quarter && coin->Weight == CoinWeight::Quarter) ? CoinValue::Quarter
        : CoinValue::Invalid;

    if(coin->Value != CoinValue::Invalid && coin->Value != CoinValue::Penny) {
        UpdateInsertedAmount(coin);
        InsertedCoins.push_back(coin);
    } else {
        ReturnSlot += static_cast<int>(coin->Value);
    }

    return coin;
}

void VendingMachine::UpdateInsertedAmount(Coin* coin)
{    
    int coinCents = static_cast<int>(coin->Value);
    InsertedAmount += coinCents;
}

int VendingMachine::GetInsertedAmount() 
{
    return InsertedAmount;
}

string VendingMachine::GetDisplay()
{
    constexpr char THANK_YOU_TEXT[] = "THANK YOU";
    constexpr char INSERT_COIN_TEXT[] = "INSERT COIN";
    constexpr char EXACT_CHANGE_TEXT[] = "EXACT CHANGE ONLY";
    constexpr char SOLD_OUT_TEXT[] = "SOLD OUT";
    constexpr string_view PRICE_FORMATTER = "PRICE ${:0.2f}";
    constexpr string_view AMOUNT_FORMATTER = "${:0.2f}";

    string message = "";
    bool canMakeChange = CanMakeChange();

    if(MessageType == MessageType::ThankYou)
    {
        // This time we show ThankYou but next time the display is checked, 
        // it should show InsertCoin
        MessageType = MessageType::InsertCoin;
        message = THANK_YOU_TEXT;
    } 
    else if (MessageType == MessageType::InsufficientFunds)
    {
        // This time we show the price but next time the display is checked, 
        // it should show the current amount in the machine
        int costCents = GetCostOf(RequestedItem);
        message = std::format(PRICE_FORMATTER, costCents / 100.0);
        MessageType = MessageType::Amount;
    }
    else if (MessageType == MessageType::Amount) {
        if(InsertedAmount == 0) {
            MessageType = MessageType::InsertCoin;
            message = canMakeChange ? INSERT_COIN_TEXT : EXACT_CHANGE_TEXT;
        } else {
            message = std::format(AMOUNT_FORMATTER, InsertedAmount / 100.0);
        }
    }
    else if (MessageType == MessageType::SoldOut) {
        // This time we show SoldOut but next time the display is checked, 
        // it should show the current amount in the machine
        MessageType = MessageType::Amount;
        message = SOLD_OUT_TEXT;
    }
    else if (GetInsertedAmount() == 0) {
        MessageType = MessageType::InsertCoin;
        message = canMakeChange ? INSERT_COIN_TEXT : EXACT_CHANGE_TEXT;
    }

    return message;
}

void VendingMachine::ClearReturnSlot()
{
    ReturnSlot = 0;
}

int VendingMachine::CountStockOf(StockedItemType itemType)
{
    return Stock[itemType];
}

void VendingMachine::AddStockOf(StockedItemType itemType, int count)
{
    Stock[itemType] += count;
}

void VendingMachine::RemoveStockOf(StockedItemType itemType, int count)
{
    Stock[itemType] -= count;
    if(Stock[itemType] < 0) {
        Stock[itemType] = 0;
    }
}

int VendingMachine::GetCostOf(StockedItemType itemType)
{
    ItemCost cost = 
        itemType == StockedItemType::Chips ? ItemCost::Chips
        : itemType == StockedItemType::Candy ? ItemCost::Candy
        : itemType == StockedItemType::Cola ? ItemCost::Cola
        : ItemCost::Invalid;
    int costCents = static_cast<int>(cost);
    return costCents;
}

void VendingMachine::RequestItem(StockedItemType itemType)
{
    int costCents = GetCostOf(itemType);

    RequestedItem = itemType;

    if(CountStockOf(itemType) == 0)
    {
        MessageType = MessageType::SoldOut;
    }
    else if(costCents > InsertedAmount) {
        MessageType = MessageType::InsufficientFunds;
    }
    else if(costCents == InsertedAmount || CanMakeChange()) {
        PutItemInFoodSlot(itemType);
        RemoveStockOf(itemType, 1);
        MessageType = MessageType::ThankYou;
        if(costCents < InsertedAmount) {
            MakeChange(InsertedAmount - costCents);
        }
        InsertedAmount = 0;
    }
    else {
        ReturnMoney();
    }
}

void VendingMachine::PutItemInFoodSlot(StockedItemType itemType)
{
    // If we were doing this on a machine, this would actually do something
}

void VendingMachine::MakeChange(int amountOfChange) {
    ChangeBank.MakeChange(amountOfChange);
    ReturnSlot += amountOfChange;
}

void VendingMachine::ReturnMoney()
{
    ReturnSlot += InsertedAmount;
    InsertedAmount = 0;
}

bool VendingMachine::CanMakeChange() {
    // 50 cents, always true
    // 55: 1 quarter, 3 dimes - need 1 nickel
    bool canMakeChangeForChips = ChangeBank.Contains(CoinValue::Nickel, 1);

    // 65 cents
    // 75: 3 quarters - need 1 dime
    // 70: 7 dimes - need 1 nickel
    bool canMakeChangeForCandy = ChangeBank.Contains(CoinValue::Dime, 1) && ChangeBank.Contains(CoinValue::Nickel, 1);

    // 100 cents
    // 105: 1 quarter, 8 dimes - need 1 nickel
    // 105: 3 quarters, 3 dimes - need 1 nickel
    bool canMakeChangeForSoda = ChangeBank.Contains(CoinValue::Nickel, 1);

    return canMakeChangeForChips && canMakeChangeForCandy && canMakeChangeForSoda;
}

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
