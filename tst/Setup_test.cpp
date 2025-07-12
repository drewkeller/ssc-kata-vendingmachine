#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(SetupTest, BasicTest)
{
    EXPECT_THAT(0, Eq(0));
    EXPECT_THAT("This test", "This test");
}
