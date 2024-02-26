#include "gtest/gtest.h"
#include "../../Number-Theory/factorization/log_factorization.cpp"


TEST(LogFactorization, SmallTest5) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize_simple(5);
    std::vector<long long> expected = {5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, TEST10) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize_simple(10);
    std::vector<long long> expected = {2, 5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, SmallTest) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize_simple(5);
    std::vector<long long> expected = {5};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, PrimeNumberTest) {
    LogFactorizer obj(19);
    std::vector<long long> facts = obj.factorize_simple(19);
    std::vector<long long> expected = {19};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, BasicTest) {
    LogFactorizer obj(10);
    std::vector<long long> facts = obj.factorize_simple(2);
    std::sort(facts.begin(), facts.end());
    std::vector<long long> expected = {2};
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, TestPrimeFreq) {
    LogFactorizer obj(120);
    std::vector<std::pair<long long, long long>> facts = obj.prime_factorize(120);
    std::sort(facts.begin(), facts.end());
    std::vector<std::pair<long long, long long>> expected = {
        {2, 3}, {3, 1}, {5, 1}
    };
    EXPECT_EQ(facts, expected);
}

TEST(LogFactorization, TestDivisors) {
    LogFactorizer obj(120);
    std::vector<long long> facts = obj.getAllDivisors(120);
    std::vector<long long> expected = {1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120};
    EXPECT_EQ(facts, expected);
}


