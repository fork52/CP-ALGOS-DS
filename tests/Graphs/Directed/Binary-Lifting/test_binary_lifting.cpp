#include "gtest/gtest.h"
#include "../../../../Graphs/Directed/Binary-Lifting/binary_lifting.cpp"

// Test binary lifting
TEST(BinaryLifting, SMALL_TEST) {
	std::vector<std::vector<int>> tree = {
		{1, 2},
		{},
		{3, 4},
		{},
		{}
	};
	int n = tree.size();
	BinaryLifting obj(n, tree);
	EXPECT_EQ(obj.lowestCommonAncestor(3, 4), 2);
	EXPECT_EQ(obj.lowestCommonAncestor(1, 4), 0);
	EXPECT_EQ(obj.lowestCommonAncestor(0, 3), 0);
}
