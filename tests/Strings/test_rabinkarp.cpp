#include "gtest/gtest.h"
#include "../../Strings/rabinkarp/rabinkarp.cpp"

TEST(RabinKarpTest, BasicTest1) {
    std::string s = "aba";
    RabinKarp rk1(s);
    RabinKarp rk2, rk3;
    rk2.push_back('a'); rk2.push_back('b'); rk2.push_back('a');
    rk3.push_front('a'); rk3.push_front('b'); rk3.push_front('a');

    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);
    EXPECT_EQ(rk3.dq, rk2.dq);
    EXPECT_EQ(rk3.hashes, rk2.hashes);

    rk2.pop_back(); // ab
    rk1.pop_front(); // ba
    rk3.pop_front(); // ba

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
    EXPECT_EQ(rk3.dq, rk1.dq);
    EXPECT_EQ(rk3.hashes, rk1.hashes);

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

    // Check if reversal of operation at back works
    rk1.push_back('a'); rk1.pop_back();
    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);

    // Check if reversal of operation at front works
    rk1.push_front('a'); rk1.pop_front();
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


TEST(RabinKarpTest, BasicTest5) {
    std::string s1 = "bc";
    std::string s2 = "ab";

    RabinKarp rk1(s1);
    RabinKarp rk2(s2);

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
    
    rk1.push_front('b');
    rk2.push_back('c');
    EXPECT_EQ(rk1.dq, rk2.dq);
    EXPECT_EQ(rk1.hashes, rk2.hashes);

    long long val1 = rk1.pop_front();
    long long val2 = rk2.pop_back();
    
    EXPECT_EQ(val1, (long long)'a');
    EXPECT_EQ(val2, (long long)'c');

    EXPECT_NE(rk1.dq, rk2.dq);
    EXPECT_NE(rk1.hashes, rk2.hashes);
}
