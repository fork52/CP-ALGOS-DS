#include "gtest/gtest.h"
#include "../../Number-Theory/sieve_factorization.cpp"

using ll = long long;

// Test prime_sieve Small
TEST(SieveFactorization, SmallTest) {
    Factorizer obj(1000);

    vector<ll> facts = obj.prime_factorize_simple(12);
    EXPECT_EQ(facts.size(), 3);
}