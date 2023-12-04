#include "gtest/gtest.h"
#include "../../Strings/poly_hash.cpp"

TEST(PolyHasher, SmallTest) {
    std::string s = "racecar";
    PolyHash H = PolyHash(std::vector<char>(s.begin(), s.end()));

    EXPECT_EQ(H.get_hash(0, 6), H.rev_hash(0, 6));
    EXPECT_EQ(H.get_hash(1, 1), H.rev_hash(5, 5));

    EXPECT_NE(H.get_hash(1, 5), H.rev_hash(0, 4));
    EXPECT_NE(H.get_hash(1, 1), H.rev_hash(5, 6));
    EXPECT_NE(H.get_hash(2, 3), H.rev_hash(2, 3));
}


TEST(PolyHasher, MediumTest) {
    PolyHash H = PolyHash(std::vector<int> {1, 2, 3, 2, 1});
    EXPECT_EQ(H.get_hash(0, 4), H.rev_hash(0, 4));
}