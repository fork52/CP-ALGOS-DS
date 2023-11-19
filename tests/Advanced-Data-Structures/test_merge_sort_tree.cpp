#include "gtest/gtest.h"
#include "../../Advanced-Data-Structures/Merge-Sort-Tree/merge_sort_tree.cpp"

// Test prime_sieve Small
TEST(MergeSortTreeTest, SmallTest)
{
  std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
  int n = arr.size();
  MergeSortTree<int> *obj = new MergeSortTree(0, arr.size() - 1, arr);

  std::vector<std::pair<int, int>> indexRanges = {
      {0, 1}, {2, n - 1}, {3, 7}, {0, n - 1}};

  std::vector<std::pair<int, int>> valueRanges = {
      {1, 10}, {3, 9}, {10, 20}, {10, 20}};

  for (int i = 0; i < indexRanges.size(); i++)
  {
    auto [l, r] = indexRanges[i];
    auto [mn, mx] = valueRanges[i];
    int cnt = 0;
    for (int j = l; j <= r; j++)
    {
      cnt += (mn <= arr[j]) && (arr[j] <= mx);
    }
    EXPECT_EQ(cnt, obj->query(l, r, mn, mx));
  }
}