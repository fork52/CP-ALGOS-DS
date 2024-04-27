#include<bits/stdc++.h>
using namespace std;

/*
Reference Problem: https://leetcode.com/problems/count-artifacts-that-can-be-extracted/
*/


/**
 * @snip-start
 * snip-name: PrefixSum-2d
 * snip-prefix: prefixsum2d
 * snip-description: Prefix Sum 2D
*/
/*
    Data structure for querying a PrefixSums over 2d ranges.
*/
template<typename T> 
class PrefixSum2D{
public:
    vector<vector<T>> pre;
    int n, m;

    /*Constructs a 2D prefix sum of matrix and stores in pre.*/
    PrefixSum2D(vector<vector<T>> mat){
        n = mat.size(), m = mat[0].size();
        pre = vector<vector<T>>(n + 1, vector<T>(m + 1, 0));
        T cur, add1, add2, sub;

        for(int r = 0; r < n; r++){
            for(int c = 0; c < m; c++){
                cur = mat[r][c];
                add1 = pre[r][c + 1];
                add2 = pre[r + 1][c];
                sub = pre[r][c];
                pre[r + 1][c + 1] = cur + add1 + add2 - sub;
            }
        }
    }
        
    /*
        Query the sum of the 2D array in the inclusive range: (r1, c1) to (r2, c2).
        s = sum(mat[r][c] for r in range(r1, r2 + 1) for c in range(c1, c2 + 1))
        Constraints: r1 <= r2 and c1 <= c2. Zero-indexed.
    */
    T query(int r1, int c1, int r2, int c2){
        T add1, add2, sub1, sub2;
        add1 = pre[r2 + 1][c2 + 1];
        add2 = pre[r1][c1];
        sub1 = pre[r2 + 1][c1];
        sub2 = pre[r1][c2 + 1];
        return add1 + add2 - sub1 - sub2;
    }
};
// @snip-end


int main(){
    vector<vector<int>> mat = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    PrefixSum2D obj(mat);
    cout << "Sum of mat is: " << obj.query(0, 0, 2, 2) << "\n";
}   