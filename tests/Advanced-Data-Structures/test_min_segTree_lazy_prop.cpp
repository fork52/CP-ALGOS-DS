#include "gtest/gtest.h"
#include "../../Advanced-Data-Structures/Segment-Tree/segTree-with-node-structure/min_segTree_lazy_prop.cpp"

// Test prime_sieve Small
TEST(MinSegTreeTest, BasicSumTest)
{
  std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
  int n = arr.size();
  MinSegTree<int> *segtree = MinSegTree<int>::create(arr);

  std::vector<std::pair<int, int>> indexRanges = {
      {0, 1}, {2, n - 1}, {3, 7}, {0, n - 1}};

  for (int i = 0; i < indexRanges.size(); i++)
  {
    auto [l, r] = indexRanges[i];
    int mn = arr[l];
    for (int j = l; j <= r; j++)
    {
      mn = std::min(mn, arr[j]);
    }
    EXPECT_EQ(mn, segtree->rangeQuery(l, r));
  }
}

TEST(MinSegTreeTest, UpdateWithSumTest)
{
  std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
  int n = arr.size();
  MinSegTree<int> *segtree = MinSegTree<int>::create(arr);

  std::vector<std::tuple<int, int, int, int>> indexRanges = {
      {1, 0, 1, 0}, {2, 1, 5, 4},
      {1, 2, n - 1, 0}, 
      {1, 3, 7, 0}, {2, 3, 7, -2}, {1, 0, n - 1, 0}, {1, 1, n - 2, 0}
    };

  for (int i = 0; i < indexRanges.size(); i++)
  {
    auto [typ, l, r, delta] = indexRanges[i];
    if(typ == 2){
        for(int j = l; j <= r; j++){
          arr[j] += delta;
        } 
        segtree->rangeUpdate(l, r, delta);
        continue;
    }
    int mn = arr[l];
    for (int j = l; j <= r; j++)
    {
      mn = std::min(mn, arr[j]);
    }
    EXPECT_EQ(mn, segtree->rangeQuery(l, r));
  }
}