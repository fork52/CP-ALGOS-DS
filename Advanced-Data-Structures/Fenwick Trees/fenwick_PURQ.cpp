#include <bits/stdc++.h>
using namespace std;
/*
Problems:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable

Fork52 Editorial:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable/editorials/4533602
    
References:
    1) Stable-Sort: https://youtu.be/uSFzHCZ4E-8
    2) Luv: https://youtu.be/DPiY9wFxGIw
    3) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
    Implementation of classic Fenwick Tree(1-based indexing) supporting:
    Point Increments/Updates and Range Queries.

    Works for reversbile functions like add, subtract, multiply

    Note:
    The fenwick array is 1-indexed unlike the orgininal array.
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
        n = arr.size() + 1;
        fenwick = vector<T1>(n, 0);
        copy(arr.begin(), arr.end(), fenwick.begin() + 1);

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
       Returns result after performing operation f(defualt:plus) for the range [ 1, i ]
    */
    T1 range_query(int i)
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
            i += i & -i;
        }
    }
};

int main()
{
    vector<long long> arr = {1, 2, 3, 4, 5, 6};
    Fenwick_Tree_PURQ<long long> FT = Fenwick_Tree_PURQ<long long>(arr);
    cout << FT.range_query(1, 4) << endl;
}