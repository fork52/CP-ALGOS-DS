#include "gtest/gtest.h"
#include "../../Number-Theory/prime_sieve.cpp"

// Test prime_sieve Small
TEST(PrimeSieveTest, SmallTest) {
  std::vector<bool> primes = bool_prime_sieve(100);

  EXPECT_EQ(primes.size(), 101);

  int primesCount = 0;
  for(auto isPrimeNum: primes){
    primesCount += isPrimeNum;
  }

  EXPECT_EQ(primesCount, 25);
}

// Test prime_sieve Medium
TEST(PrimeSieveTest, MediumTest) {
  std::vector<bool> primes = bool_prime_sieve(1000);

  EXPECT_EQ(primes.size(), 1001);

  int primesCount = 0;
  for(auto isPrimeNum: primes){
    primesCount += isPrimeNum;
  }

  EXPECT_EQ(primesCount, 168);
}

 
// Test prime_sieve Large
TEST(PrimeSieveTest, LargeTest) {
  std::vector<bool> primes = bool_prime_sieve(100000);

  EXPECT_EQ(primes.size(), 100001);

  int primesCount = 0;
  for(auto isPrimeNum: primes){
    primesCount += isPrimeNum;
  }

  EXPECT_EQ(primesCount, 9592);
}