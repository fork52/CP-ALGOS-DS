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
    Implementation of Fenwick Tree supporting:
    Point Increments/Updates and Range Queries.

    Works for reversbile functions like add, subtract, multiply

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

public:
    // Empty Constructor
    Fenwick_Tree() {}

    /* Constructs a Fenwick Tree for the given array*/
    Fenwick_Tree(vector<T1> &arr)
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

    /*Returns the sum of elements from 1....i in arr*/
    T1 range_query(int i)
    {
        T1 total = 0;
        while (i > 0)
        {
            total += fenwick[i];
            total = f(total, fenwick[i]);
            i -= i & -i; //flip last set bit
        }
        return total;
    }

    T1 range_query(int l, int r)
    {
        return f_rev(range_query(r), range_query(l - 1));
    }

    T1 range_query_0indexed(int i)
    {
        return range_query(i + 1);
    }

    T1 range_query_0indexed(int l, int r)
    {
        return f_rev(range_query_0indexed(r + 1), range_query_0indexed(l));
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

    void point_update_0indexed(int i, T1 x)
    {
        return point_update(i + 1, x);
    }
};

int main()
{
    vector<long long> arr = {1, 2, 3, 4, 5, 6};
    Fenwick_Tree<long long> FT = Fenwick_Tree<long long>(arr);
    cout << FT.range_query(1, 4) << endl;
}