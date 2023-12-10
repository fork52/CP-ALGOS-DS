#include "gtest/gtest.h"
#include "../../Advanced-Data-Structures/Sparse-Table/sparse_table.cpp"
#include <algorithm>

TEST(SparseTable, MinTest)
{
    std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
    SparseTable sparseTable(arr, [](int a, int b)
                            { return a < b ? a : b; });

    for(int i = 0; i < arr.size(); i++){
        int mn = arr[i];
        for(int j = i; j < arr.size(); j++){
            mn = std::min(arr[j], mn);
            EXPECT_EQ(mn, sparseTable.query(i, j));
        }
    }
}

TEST(SparseTable, MaxTest)
{
    std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
    SparseTable sparseTable(arr, [](int a, int b)
                            { return a > b ? a : b; });

    for(int i = 0; i < arr.size(); i++){
        int mn = arr[i];
        for(int j = i; j < arr.size(); j++){
            mn = std::max(arr[j], mn);
            EXPECT_EQ(mn, sparseTable.query(i, j));
        }
    }
}

TEST(SparseTable, GcdTest)
{
    std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
    SparseTable sparseTable(arr, [](int a, int b)
                            { return std::__gcd(a, b); });

    for(int i = 0; i < arr.size(); i++){
        int mn = arr[i];
        for(int j = i; j < arr.size(); j++){
            mn = std::__gcd(arr[j], mn);
            EXPECT_EQ(mn, sparseTable.query(i, j));
        }
    }
}