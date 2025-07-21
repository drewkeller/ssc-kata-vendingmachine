#include "CoinStore.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace VendingMachines;

class CoinStoreTest : public testing::Test {
public:
    CoinStore CoinStore;
};

TEST_F(CoinStoreTest, WHEN_Cleared_THEN_ContainsNoCoins)
{
    CoinStore.Fill(1, 2, 3);
    CoinStore.Clear();
    EXPECT_THAT(0, CoinStore.Value);
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Quarter, 1));
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Dime, 1));
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Nickel, 1));
}

TEST_F(CoinStoreTest, WHEN_Filled_THEN_ContainsCorrectCoins)
{
    CoinStore.Fill(1, 2, 3);
    EXPECT_THAT(60, CoinStore.Value);
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Quarter, 1));
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Dime, 2));
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Nickel, 3));
}

TEST_F(CoinStoreTest, WHEN_Remove_THEN_ContainsCorrectCoins)
{
    CoinStore.Fill(1, 2, 3);
    EXPECT_THAT(60, CoinStore.Value);
    
    // remove the quarter
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Quarter, 1));
    CoinStore.Remove(CoinValue::Quarter, 1);
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Quarter, 1));
    EXPECT_THAT(35, CoinStore.Value);

    // remove one dime
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Dime, 2));
    CoinStore.Remove(CoinValue::Dime, 1);
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Dime, 2));
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Dime, 1));
    EXPECT_THAT(25, CoinStore.Value);

    // remove the other dime
    CoinStore.Remove(CoinValue::Dime, 1);
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Dime, 1));
    EXPECT_THAT(15, CoinStore.Value);
    
    // remoev all the nickels
    EXPECT_THAT(true, CoinStore.Contains(CoinValue::Nickel, 3));
    CoinStore.Remove(CoinValue::Nickel, 3);
    EXPECT_THAT(0, CoinStore.Value);
    EXPECT_THAT(false, CoinStore.Contains(CoinValue::Nickel, 1));
}

TEST_F(CoinStoreTest, WHEN_CanMakeChange_THEN_ReturnsCorrectValue)
{
    CoinStore.Clear();
    EXPECT_THAT(false, CoinStore.CanMakeChange(5));

    CoinStore.Add(CoinValue::Nickel, 1);
    EXPECT_THAT(true, CoinStore.CanMakeChange(5));
    EXPECT_THAT(false, CoinStore.CanMakeChange(10));

    CoinStore.Add(CoinValue::Quarter, 1);
    EXPECT_THAT(false, CoinStore.CanMakeChange(10));
    EXPECT_THAT(true, CoinStore.CanMakeChange(25));
    EXPECT_THAT(true, CoinStore.CanMakeChange(30));

    CoinStore.Add(CoinValue::Dime, 1);
    EXPECT_THAT(true, CoinStore.CanMakeChange(10));
    EXPECT_THAT(true, CoinStore.CanMakeChange(35));
    EXPECT_THAT(true, CoinStore.CanMakeChange(40));
}

TEST_F(CoinStoreTest, WHEN_MakeChange_THEN_CoinStoreIsUpdated)
{
    CoinStore.Fill(1, 1, 1);
    CoinStore.MakeChange(40);
    EXPECT_THAT(0, CoinStore.Value);

    CoinStore.Fill(2, 1, 1);
    CoinStore.MakeChange(40);
    EXPECT_THAT(25, CoinStore.Value);
}

