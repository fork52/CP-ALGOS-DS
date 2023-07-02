#include <bits/stdc++.h>
using namespace std;

/*
References:
http://www.spoj.com/problems/RMQSQ/
https://cp-algorithms.com/data_structures/sparse-table.html
*/

/* 
    Sparse Table for Range Minimum Queries.
    Change the Function for Max Queries.

    Assumptions: 
        Array is 0-indexed.
        Queries are range inclusive
*/
class Sparse_Table{
public:
    int **sp_table;
    int MAX_N , LOG_N;

    /* Returns no_bits - 1 */
    int log_base_2(int n){
        int bits = 0;
        while(n){
            n >>= 1;
            bits++;
        }
        return bits - 1;
    }

    /* 
        Constructs a Sparse Table for querying the given array
        Time Complexity : O( N * log(N) )
        Space Complexity: O( N * log(N) )
    */
    Sparse_Table(vector<int> &arr){

        MAX_N = arr.size();
        LOG_N = log_base_2(MAX_N);

        sp_table = new int*[MAX_N];
        for(int i = 0; i < MAX_N ; i++){
            sp_table[i] = new int[LOG_N + 1];
        }

        // Initialize the first column
        for(int i=0; i < MAX_N ; i++){
            sp_table[i][0] = arr[i];
        }

        // Preprocessing -> O( N * log(N) )
        for(int j=1 ; j <= LOG_N; j++){
            for(int i = 0; i + (1 << j) - 1 < MAX_N ; i++  ){
                // Here we are taking min. Change this to change functionality.
                sp_table[i][j] = min( sp_table[i][j-1] ,  sp_table[i + (1<<(j-1))][j-1]);
            }
        }

    }

    /* 
        Returns the minimum in the range [L ,R] inclusive. 
        Time Complexity : O(1)
    */
    int query(int L , int R){
        int qspan = R - L + 1;
        int k = log_base_2(qspan);
        return min(sp_table[L][k] , sp_table[R - (1<<k) + 1][k] ); 
    }

};

int main(){
    int n , t , q , L , R;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> arr;
    for(int i = 0 ; i < n; i++){
        cin >> t;
        arr.push_back(t); 
    }

    Sparse_Table SparseT = Sparse_Table(arr);

    cin >> q;
    for( int i = 0 ; i < q ; i++ ){
        cin >> L >> R;
        cout << SparseT.query(L , R) << endl;
    }

}