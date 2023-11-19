#include "gtest/gtest.h"
#include "../../../../Graphs/Directed/Binary-Lifting/kth_ancestor.cpp"


// Test kth Ancestor of Node.
TEST(kthAncestorOfNode, SMALL_TEST) {
	std::vector<std::vector<int>> tree = {
		{1, 2},
		{},
		{3, 4},
		{},
		{}
	};
	int n = tree.size();
	KthAncestorOfNode obj(n, tree);
	EXPECT_EQ(obj.findKthAncestor(3, 1), 2);
	EXPECT_EQ(obj.findKthAncestor(3, 2), 0);
	EXPECT_EQ(obj.findKthAncestor(3, 3), -1);
}


// Test kth Ancestor of Node.
TEST(kthAncestorOfNode, TRICKY_TEST) {
	std::vector<std::vector<int>> tree = {
		{1}, {}
	};
	int n = tree.size();
	KthAncestorOfNode obj(n, tree);
	EXPECT_EQ(obj.findKthAncestor(1, 2), -1);
	EXPECT_EQ(obj.findKthAncestor(1, 1), 0);
}