#include <bits/stdc++.h>
using namespace std;

/*
Problems:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable

My Editorial:
    https://binarysearch.com/problems/Range-Query-on-a-List-Mutable/editorials/4533602
    
References:
    1) Stable-Sort: https://youtu.be/uSFzHCZ4E-8
    2) Luv: https://youtu.be/DPiY9wFxGIw
    3) CP-algos: https://cp-algorithms.com/data_structures/fenwick.html
*/

template< typename T1>
/*
    Note:
    The fenwick array is 1-indexed unlike the orgininal array 
*/
class Fenwick_Tree{
public:
    int n;
    vector<T1> fenwick;

    // Empty Constructor
    Fenwick_Tree(){}

    /* Constructs a Fenwick Tree for the given array*/
    Fenwick_Tree(vector<T1> &arr){
        n = arr.size() + 1;
        fenwick = vector<T1>( n , 0 );

        copy(arr.begin(), arr.end(), fenwick.begin() + 1);

        int parent_ind;
        for(int i = 1; i < n; i++){
            parent_ind = i + (i & -i);
            if(parent_ind < n){
                fenwick[parent_ind] += fenwick[i];
            }
        }
    }


    /*Returns the sum of elements from 1....i in arr*/
    int query(int i){
        T1 total = 0;
        while( i > 0){
            total += fenwick[i];
            i -= i & -i;   //flip last set bit
        }
        return total;
    }

    /* Add certain value 'x' to index i */
    void add(int i, T1 x){
        while(i < n){
            fenwick[i] += x;
            i += i & -i;
        }
    }

};


int main(){
    vector<long long> arr = {1,2,3,4,5,6};
    Fenwick_Tree<long long> FT = Fenwick_Tree<long long>(arr);
    cout << FT.query(6) << endl; 
}