#include "gtest/gtest.h"
#include "../../Number-Theory/factorization/sieve_factorization.cpp"

using ll = long long;

TEST(SieveFactorization, SmallTest) {
    Factorizer obj(1000);

    vector<ll> facts = obj.prime_factorize_simple(12);
    vector<ll> expected = {2, 2, 3};
    EXPECT_EQ(facts.size(), 3);
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, PrimeNumberTest) {
    Factorizer obj(19);
    vector<ll> facts = obj.prime_factorize_simple(19);
    vector<ll> expected = {19};
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, CheckPrimes) {
    Factorizer obj(66120);
    vector<ll> facts = obj.prime_factorize_simple(66120);
    vector<ll> expected = {2, 2, 2, 3, 5, 19, 29};
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, BasicTest) {
    Factorizer obj(2);
    vector<ll> facts = obj.prime_factorize_simple(2);
    vector<ll> expected = {2};
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, CheckPrimes100) {
    Factorizer obj(100);
    vector<ll> facts = obj.prime_factorize_simple(100);
    vector<ll> expected = {2, 2, 5, 5};
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, CheckDivisorsSmall) {
    Factorizer obj(12);
    vector<ll> facts = obj.getAllDivisors(12);
    vector<ll> expected = {1, 2, 3, 4, 6, 12};
    EXPECT_EQ(facts, expected);
}

TEST(SieveFactorization, CheckDivisorsLarge) {
    Factorizer obj(120);
    vector<ll> facts = obj.getAllDivisors(120);
    vector<ll> expected = {1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120};
    EXPECT_EQ(facts, expected);
}