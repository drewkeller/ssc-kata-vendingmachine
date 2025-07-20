#include "VendingMachine.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace VendingMachines;

TEST(VendingMachineTest, WHEN_NoCoinsInserted_THEN_DisplaysInsertCoin)
{
     VendingMachine vendingMachine;
     EXPECT_THAT(0, vendingMachine.GetInsertedAmount());
     EXPECT_THAT("INSERT COIN", vendingMachine.GetDisplay());
}
