#include <bits/stdc++.h>
using namespace std;

template< typename T1>
class Fenwick_Tree{
public:
    int n;
    vector<T1> fenwick;

    // Empty Constructor
    Fenwick_Tree(){}

    /* Constructs a Fenwick Tree for the given array*/
    Fenwick_Tree(int size){
        n = size + 1;
        fenwick = vector<T1>( n , 0 );
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


/*
    If arr is of size n, the function rescales
    all the elements present in the array in 
    the range 1 .... min(n, no_of_unique_elements)

    Modifies the array in place.

    
*/
void rescale(vector<int> &arr){
    
    vector<int> cpy = arr;
    
    sort(cpy.begin() , cpy.end() );

    map<int,int> seen;
    int n = arr.size();
    int cur = 1;

    for(int i = 0; i < n ; i++ ){
        if(!seen.count(cpy[i])){
            seen[cpy[i]] = cur;
            cur++;
        }
    }

    for(int i=0; i < n ; i++){
        arr[i] = seen[arr[i]];
    }
}




int main(){
    vector<int> arr = {1,15,5,10,7,8};

    rescale(arr);

    cout << "Rescaled Array: " ; 
    for(auto no : arr){
        cout << no << " ";
    }
    cout << endl;

    int maxe = *max_element(arr.begin() , arr.end());

    Fenwick_Tree<int> FT = Fenwick_Tree<int>(maxe);


    // For counting inversions in the array
    int count = 0 ;


    for(int i=0; i < arr.size() ; i++){
        int no = arr[i];
        count += FT.query(maxe) - FT.query(no);
        FT.add(no , 1);
    }

    cout << "Total No of Inversions: " << count << endl; 
}