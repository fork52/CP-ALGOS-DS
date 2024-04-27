#include <bits/stdc++.h>
using namespace std;

/*
Related Problems:
    - https://binarysearch.com/problems/Range-Update
    
References:
    1) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/


/**
 * @snip-start
 * snip-name: FenwickTree Point Query Range Update
 * snip-prefix: fenwick_PQRU
 * snip-description: FenwickTree Point Query Range Update
*/
/*
    Implementation of Fenwick Tree supporting:
    Range Increments and point query

    Note:
    The fenwick array is 1-indexed unlike the orgininal array.
    Please keep this in mind when you query!
*/
template <typename T1>
class Fenwick_Tree_PQRU
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

    /* 
        Performs f ( fenwick[i], delta )
        By default adds delta at index i.
    */
    void point_add(int i, T1 delta)
    {
        while (i < n)
        {
            fenwick[i] = f(fenwick[i], delta);
            i += i & -i;
        }
    }

public:
    // Empty Constructor
    Fenwick_Tree_PQRU() {}

    /* 
        Constructs a Fenwick Tree(1 - indexed) for the given array of size n+1
        Time: O(n)
    */
    Fenwick_Tree_PQRU(vector<T1> &arr)
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
            total = f(total, fenwick[i]);
            i -= i & -i; //flip last set bit
        }
        return total;
    }

    /*
        Performs f(fenwick[i], delta) for all l <= i <= r
        Assumes 1 based indexing
        Time : O(logn * 2)
    */
    void range_update(int l, int r, int delta)
    {
        point_add(l, delta);
        point_add(r + 1, -delta);
    }
};
// @snip-end
