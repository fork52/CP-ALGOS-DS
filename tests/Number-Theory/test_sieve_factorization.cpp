#include "gtest/gtest.h"
#include "../../Number-Theory/sieve_factorization.cpp"

using ll = long long;

// Test sieve factorize Small
TEST(SieveFactorization, SmallTest) {
    Factorizer obj(1000);

    vector<ll> facts = obj.prime_factorize_simple(12);
    vector<ll> expected = {2, 2, 3};
    EXPECT_EQ(facts.size(), 3);
    EXPECT_EQ(facts, expected);
}

// Test sieve factorize prime
TEST(SieveFactorization, PrimeNumberTest) {
    Factorizer obj(1000);

    vector<ll> facts = obj.prime_factorize_simple(19);
    vector<ll> expected = {19};
    EXPECT_EQ(facts.size(), 1);
    EXPECT_EQ(facts, expected);
}