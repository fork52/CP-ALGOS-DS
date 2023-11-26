#include "gtest/gtest.h"
#include "../../Number-Theory/factorization/log_factorization.cpp"


TEST(LogFactorization, SmallTest5) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize(5);
    std::vector<long long> expected = {5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, TEST10) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize(10);
    std::vector<long long> expected = {2, 5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, SmallTest) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize(5);
    std::vector<long long> expected = {5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, PrimeNumberTest) {
    LogFactorizer obj(19);
    std::vector<long long> facts = obj.factorize(19);
    std::vector<long long> expected = {19};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, BasicTest) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize(2);
    std::sort(facts.begin(), facts.end());
    std::vector<long long> expected = {2};
    EXPECT_EQ(facts, expected);
}
