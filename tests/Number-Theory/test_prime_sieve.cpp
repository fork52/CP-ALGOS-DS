#include "gtest/gtest.h"
#include "../../Number-Theory/prime_sieve.cpp"
#include <numeric>

// Test prime_sieve Small
TEST(PrimeSieveTest, SmallTest) {
  int n = 100;
  std::vector<bool> primes = bool_prime_sieve(n);
  EXPECT_EQ(primes.size(), n + 1);

  int primesCount = std::accumulate(primes.begin(), primes.end(), 0);

  EXPECT_EQ(primesCount, 25);
}

// Test prime_sieve Medium
TEST(PrimeSieveTest, MediumTest) {
  int n = 1000;
  std::vector<bool> primes = bool_prime_sieve(n);
  EXPECT_EQ(primes.size(), n + 1);
  int primesCount = std::accumulate(primes.begin(), primes.end(), 0);
  EXPECT_EQ(primesCount, 168);

}

// Test prime_sieve Large
TEST(PrimeSieveTest, LargeTest) {
  int n = 100000;
  std::vector<bool> primes = bool_prime_sieve(n);
  EXPECT_EQ(primes.size(), n + 1);
  int primesCount = std::accumulate(primes.begin(), primes.end(), 0);
  EXPECT_EQ(primesCount, 9592);
}


// Test Bit Set
TEST(PrimeSieveTest, BitSetTest) {
  EXPECT_EQ(bits_prime_sieve(1e5).count(), 9592);
}