#include <bits/stdc++.h>
using namespace std;

/*

References:
    1) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
    Implementation of Fenwick Tree supporting:
    Range Increments and point query

    Note:
    The fenwick array is 1-indexed unlike the orgininal array.
    Please keep this in mind when you query!
*/
template <typename T1>
class Fenwick_Tree
{
public:
    int n;
    vector<T1> fenwick;

private:
    inline T1 f(T1 x, T1 y)
    {
        return x + y;
    }
    inline T1 f_rev(T1 x, T1 y)
    {
        return x - y;
    }
    /* Add certain value 'x' to index i */
    void point_update(int i, T1 x)
    {
        while (i < n)
        {
            fenwick[i] = f(fenwick[i], x);
            i += i & -i;
        }
    }

public:
    // Empty Constructor
    Fenwick_Tree() {}

    /* 
        Constructs a Fenwick Tree(1 - indexed) for the given array of size n+1
        Time: O(n)
    */
    Fenwick_Tree(vector<T1> &arr)
    {
        n = arr.size() + 1;
        fenwick = vector<T1>(n, 0);

        int cur_sum = 0;

        for (int i = 0; i < n - 1; i++)
        {
            fenwick[i + 1] = arr[i] - cur_sum;
            cur_sum = f(cur_sum, f_rev(arr[i], cur_sum));
        }

        int parent_ind;
        for (int i = 1; i < n; i++)
        {
            parent_ind = i + (i & -i);
            if (parent_ind < n)
            {
                fenwick[parent_ind] = f(fenwick[parent_ind], fenwick[i]);
            }
        }
    }

    /*
        Returns the value at index i
        Assumes 1 based indexing
        Time: O(logn)
    */

    T1 point_query(int i)
    {
        T1 total = 0;
        while (i > 0)
        {
            total += fenwick[i];
            i -= i & -i; //flip last set bit
        }
        return total;
    }

    T1 point_query_0indexed(int i)
    {
        return point_query(i + 1);
    }

    /*
        Increments values in the range l,l+1,... r by val
        Assumes 1 based indexing
        Time : O(logn * 2)
    */
    void range_update(int l, int r, int val)
    {
        point_update(l, val);
        point_update(r + 1, -val);
    }

    void range_update_0indexed(int l, int r, int val)
    {
        range_update(l + 1, r + 1, val);
    }
};
int main()
{
    vector<long long> arr = {1, 2, 3, 4, 5, 6};
    Fenwick_Tree FT = Fenwick_Tree(arr);

    for (int ind = 1; ind <= arr.size(); ind++)
    {
        cout << FT.point_query(ind) << " ";
    }
    cout << endl;

    FT.range_update(2, 3, 10);

    for (int ind = 1; ind <= arr.size(); ind++)
    {
        cout << FT.point_query(ind) << " ";
    }
    cout << endl;
}