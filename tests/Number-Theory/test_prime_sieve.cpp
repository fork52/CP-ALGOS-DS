#include "gtest/gtest.h"
#include "../../Number-Theory/prime_sieve.cpp"

// Demonstrate some basic assertions.
TEST(PrimeSieveTest, BasicTest) {
  // Expect two strings not to be equal.
  std::vector<bool> primes = bool_prime_sieve(100);

  EXPECT_EQ(primes.size(), 101);

  int primesCount = 0;
  for(auto isPrimeNum: primes){
    primesCount += isPrimeNum;
  }

  EXPECT_EQ(primesCount, 25);
}

