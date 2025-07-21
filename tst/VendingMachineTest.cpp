#include "VendingMachine.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace VendingMachines;

class VendingMachineTest : public testing::Test {
protected:
    void SetUp() {
        VendingMachine.ChangeBank.Fill(5, 5, 5);
    }
public:
    VendingMachine VendingMachine;
};

TEST_F(VendingMachineTest, WHEN_NoCoinsInserted_THEN_DisplaysInsertCoin)
{
     EXPECT_THAT(0, VendingMachine.GetInsertedAmount());
     EXPECT_THAT("INSERT COIN", VendingMachine.GetDisplay());
}

TEST_F(VendingMachineTest, WHEN_ValidCoinIsInserted_THEN_CoinIsRecognized)
{
    Coin dime(CoinSize::Dime, CoinWeight::Dime);
    Coin nickel(CoinSize::Nickel, CoinWeight::Nickel);
    Coin quarter(CoinSize::Quarter, CoinWeight::Quarter);
    EXPECT_THAT(dime.Value == CoinValue::Dime, VendingMachine.InsertCoin(&dime));
    EXPECT_THAT(nickel.Value == CoinValue::Nickel, VendingMachine.InsertCoin(&nickel));
    EXPECT_THAT(quarter.Value == CoinValue::Quarter, VendingMachine.InsertCoin(&quarter));
}

TEST_F(VendingMachineTest, WHEN_InvalidCoinIsInserted_THEN_CoinIsRejected)
{
    Coin penny(CoinSize::Penny, CoinWeight::Penny);
    Coin nickel(CoinSize::Nickel, CoinWeight::Nickel);
    VendingMachine.InsertCoin(&penny);
    EXPECT_THAT(1, VendingMachine.ReturnSlot);
}

TEST_F(VendingMachineTest, WHEN_CoinIsInserted_THEN_InsertedAmountUpdatesCorrectly)
{
    Coin nickel(CoinSize::Nickel, CoinWeight::Nickel);
    VendingMachine.InsertCoin(&nickel);
    EXPECT_EQ(5, VendingMachine.GetInsertedAmount());
}

TEST_F(VendingMachineTest, WHEN_TwoCoinsAreInserted_THEN_InsertedAmountUpdatesCorrectly)
{
    Coin nickel(CoinSize::Nickel, CoinWeight::Nickel);
    Coin quarter(CoinSize::Quarter, CoinWeight::Quarter);
    VendingMachine.InsertCoin(&quarter);
    VendingMachine.InsertCoin(&nickel);
    EXPECT_EQ(30, VendingMachine.GetInsertedAmount());
}

TEST_F(VendingMachineTest, WHEN_ClearReturnSlot_THEN_ReturnSlotContainsNothing)
{
    Coin penny(CoinSize::Penny, CoinWeight::Penny);
    VendingMachine.InsertCoin(&penny);
    EXPECT_THAT(1, VendingMachine.ReturnSlot);
    VendingMachine.ClearReturnSlot();
    EXPECT_THAT(0, VendingMachine.ReturnSlot);
}

TEST_F(VendingMachineTest, WHEN_AddingStock_THEN_CountIsCorrect)
{
    EXPECT_THAT(0, VendingMachine.CountStockOf(StockedItemType::Cola));
    VendingMachine.AddStockOf(StockedItemType::Cola, 1);
    EXPECT_THAT(1, VendingMachine.CountStockOf(StockedItemType::Cola));
    VendingMachine.AddStockOf(StockedItemType::Cola, 2);
    EXPECT_THAT(3, VendingMachine.CountStockOf(StockedItemType::Cola));
}

TEST_F(VendingMachineTest, GIVEN_ExactFunds_WHEN_ProductOrdered_THEN_ProductIsDispensed)
{
    Coin quarter1(CoinSize::Quarter, CoinWeight::Quarter);
    Coin quarter2(CoinSize::Quarter, CoinWeight::Quarter);
    VendingMachine.AddStockOf(StockedItemType::Chips, 2);
    VendingMachine.InsertCoin(&quarter1);
    VendingMachine.InsertCoin(&quarter2);
    VendingMachine.RequestItem(StockedItemType::Chips);
    EXPECT_THAT(0, VendingMachine.GetInsertedAmount());
    EXPECT_THAT(1, VendingMachine.CountStockOf(StockedItemType::Chips));
    EXPECT_THAT("THANK YOU", VendingMachine.GetDisplay());
    EXPECT_THAT("INSERT COIN", VendingMachine.GetDisplay());
}

TEST_F(VendingMachineTest, GIVEN_NoCoinsInserted_WHEN_ProductOrdered_THEN_ProductIsDispensed)
{
    VendingMachine.AddStockOf(StockedItemType::Chips, 2);
    VendingMachine.RequestItem(StockedItemType::Chips);
    EXPECT_THAT(2, VendingMachine.CountStockOf(StockedItemType::Chips));
    // first check shows price of item
    EXPECT_THAT("PRICE $0.50", VendingMachine.GetDisplay());
    // second check shows current amount
    EXPECT_THAT("INSERT COIN", VendingMachine.GetDisplay());
}

TEST_F(VendingMachineTest, GIVEN_InsufficientFunds_WHEN_ProductOrdered_THEN_ProductIsDispensed)
{
    Coin quarter1(CoinSize::Quarter, CoinWeight::Quarter);
    VendingMachine.AddStockOf(StockedItemType::Chips, 2);
    VendingMachine.InsertCoin(&quarter1);
    VendingMachine.RequestItem(StockedItemType::Chips);
    EXPECT_THAT(2, VendingMachine.CountStockOf(StockedItemType::Chips));
    // first check shows price of item
    EXPECT_THAT("PRICE $0.50", VendingMachine.GetDisplay());
    // second check shows current amount
    EXPECT_THAT("$0.25", VendingMachine.GetDisplay());
}

TEST_F(VendingMachineTest, GIVEN_MoreThanSufficientFunds_WHEN_ProductOrdered_THEN_ReturnsChange)
{
    int overPayment = ((int)CoinValue::Quarter * 3) - (int)ItemCost::Candy;
    Coin quarter1(CoinSize::Quarter, CoinWeight::Quarter);
    Coin quarter2(CoinSize::Quarter, CoinWeight::Quarter);
    Coin quarter3(CoinSize::Quarter, CoinWeight::Quarter);
    VendingMachine.AddStockOf(StockedItemType::Candy, 2);
    VendingMachine.InsertCoin(&quarter1);
    VendingMachine.InsertCoin(&quarter2);
    VendingMachine.InsertCoin(&quarter3);
    VendingMachine.RequestItem(StockedItemType::Candy);
    EXPECT_THAT(overPayment, VendingMachine.ReturnSlot);
    EXPECT_THAT(0, VendingMachine.GetInsertedAmount());
    EXPECT_THAT(1, VendingMachine.CountStockOf(StockedItemType::Candy));
    EXPECT_THAT("THANK YOU", VendingMachine.GetDisplay());
    EXPECT_THAT("INSERT COIN", VendingMachine.GetDisplay());
}

TEST_F(VendingMachineTest, GIVEN_RequestedItemIsSoldOut_WHEN_ItemRequested_THEN_DisplayShowsSoldOut)
{
    Coin quarter1(CoinSize::Quarter, CoinWeight::Quarter);
    Coin quarter2(CoinSize::Quarter, CoinWeight::Quarter);
    VendingMachine.InsertCoin(&quarter1);
    VendingMachine.InsertCoin(&quarter2);
    VendingMachine.RequestItem(StockedItemType::Chips);
    EXPECT_THAT(0, VendingMachine.ReturnSlot);
    EXPECT_THAT(50, VendingMachine.GetInsertedAmount());
    EXPECT_THAT(0, VendingMachine.CountStockOf(StockedItemType::Chips));
    EXPECT_THAT("SOLD OUT", VendingMachine.GetDisplay());
    EXPECT_THAT("$0.50", VendingMachine.GetDisplay());    
}

TEST_F(VendingMachineTest, GIVEN_CannotMakeChange_THEN_DisplayShowsExactChangeOnly) {
    VendingMachine.ChangeBank.Clear();
    EXPECT_THAT("EXACT CHANGE ONLY", VendingMachine.GetDisplay());
}
