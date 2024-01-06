#include "gtest/gtest.h"
#include "../../Combinatorics/general.cpp"

// Test combinatorics smalltest
TEST(CombinatoricsTest, SmallTest)
{
    std::vector<long long> comb4 = {1, 4, 6, 4, 1};
    Combinatorics comb;

    for(int i = 0; i < comb4.size(); i++){
        ASSERT_EQ(comb.nCr(4, i), comb4[i]);
    }
}

// Test combinatorics large test
TEST(CombinatoricsTest, LargeTest)
{
    std::vector<long long> comb5 = {1, 5, 10, 10, 5, 1};
    Combinatorics comb;

    for(int i = 0; i < comb5.size(); i++){
        ASSERT_EQ(comb.nCr(5, i), comb5[i]);
    }
}