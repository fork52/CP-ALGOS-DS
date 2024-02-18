#include "gtest/gtest.h"
#include "../../Strings/rabinkarp/rabinkarp.cpp"

TEST(RabinKarpTest, BasicTest1) {
    std::string s = "abc";
    RabinKarp rk1(s);
    RabinKarp rk2;
    rk2.push_back('a');
    rk2.push_back('b');
    rk2.push_back('c');

    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);
}

TEST(RabinKarpTest, BasicTest2) {
    std::string s1 = "abc";
    std::string s2 = "abd";

    RabinKarp rk1(s1);
    RabinKarp rk2(s2);

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
}


TEST(RabinKarpTest, BasicTest3) {
    std::string s1 = "ab";
    std::string s2 = "abd";

    RabinKarp rk1(s1);
    RabinKarp rk2(s2);

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
    
    rk1.push_back('d');
    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);
}

TEST(RabinKarpTest, BasicTest4) {
    std::string s1 = "bd";
    std::string s2 = "abd";

    RabinKarp rk1(s1);
    RabinKarp rk2(s2);

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
    
    long long val = rk2.pop_front();
    EXPECT_EQ(val, (long long)'a');
    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);
}

