#include <bits/stdc++.h>
using namespace std;
/*
References:
    CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
    Implementation of classic Fenwick Tree(0-based indexing) supporting:
    Point Increments/Updates and Range Queries.

    Works for reversbile functions like add, subtract, multiply

    Note:
        The fenwick array is 0-indexed.
        Please keep this in mind when you query!
*/
template <typename T1>
class Fenwick_Tree_PURQ
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

public:
    // Empty Constructor
    Fenwick_Tree_PURQ() {}

    /* Constructs a Fenwick Tree for the given array*/
    Fenwick_Tree_PURQ(vector<T1> &arr)
    {
        n = arr.size();
        fenwick = vector<T1>(n, 0);
        copy(arr.begin(), arr.end(), fenwick.begin());

        int parent_ind;
        for (int i = 0; i < n; i++)
        {
            parent_ind = i | (i+1);
            if (parent_ind < n)
            {
                fenwick[parent_ind] = f(fenwick[parent_ind], fenwick[i]);
            }
        }
    }

    /*
       Returns result after performing operation f(defualt:plus) for the range [ 1, i ]
    */
    T1 range_query(int i)
    {
        T1 total = 0;
        while (i >= 0)
        {
            total = f(total, fenwick[i]);
            i = ( i & (i+1) ) - 1; //flip last set bit
        }
        return total;
    }

    /*  
        Returns result after performing operation f(defualt:plus) for the range [ l, r ] 
    */
    T1 range_query(int l, int r)
    {
        return f_rev(range_query(r), range_query(l - 1));
    }

    /* 
        Performs f ( fenwick[i], delta )
        By default adds delta at index i.
    */
    void point_add(int i, T1 delta)
    {
        #ifdef DEBUG
                assert(i > 0 && i < n);
        #endif
        while (i < n)
        {
            fenwick[i] = f(fenwick[i], delta);
            i = i | (i+1);
        }
    }
};

// int main()
// {
//     vector<long long> arr = {1, 2, 3, 4, 5, 6};
//     Fenwick_Tree_PURQ<long long> FT = Fenwick_Tree_PURQ<long long>(arr);
//     cout << FT.range_query(0, 3) << endl;
//     FT.point_add(0,99);
//     cout << FT.range_query(0,0) << endl;
// }