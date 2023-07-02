#include <bits\stdc++.h>

using namespace std;
using ll = long long;


template<typename T1>
void disp_vec(vector<T1> arr){
    int n = arr.size();
    for(auto a: arr){
        cout << a << " ";
    }
    cout << "\n";
}

/*
References:
    https://youtu.be/QvgpIX4_vyA

Related Problems:
    https://cses.fi/problemset/task/1648/
*/

template<typename T1>
class MinSegmentTree{
public:
    static const ll identity = INT64_MAX;
    T1 nodeLeft, nodeRight;
    MinSegmentTree *leftChild, *rightChild;
    T1 nodeMin;

    /* Constructs a segment tree from the array passed*/
    MinSegmentTree(T1 nodeLeft, T1 nodeRight, vector<T1>& arr){
        this -> nodeLeft = nodeLeft;
        this -> nodeRight = nodeRight;
        this -> leftChild = this -> rightChild = nullptr;

        if( isLeaf() ){
            nodeMin = arr[nodeLeft];
        }
        else{
            T1 mid = (nodeRight - nodeLeft) / 2 + nodeLeft;
            this -> leftChild = new MinSegmentTree(nodeLeft, mid, arr);
            this -> rightChild = new MinSegmentTree(mid + 1, nodeRight, arr);
            this -> recalculate();
        }
    }

    /* Returns if current node is a leaf*/
    bool isLeaf(){
        return this -> nodeLeft == this -> nodeRight;
    }

    /* Recalculates the min for current node using left and right child mins*/
    void recalculate(){
        if( isLeaf() ) return;
        nodeMin = min(leftChild -> nodeMin, rightChild -> nodeMin);
    }

    void pointUpdate(int index, int newVal){
        if( isLeaf() ){
            nodeMin = newVal;
            return;
        }

        if( index <= leftChild -> nodeRight){
            leftChild -> pointUpdate(index, newVal);
        }
        else{
            rightChild -> pointUpdate(index, newVal);
        }
        this -> recalculate();
    }

    T1 rangeSum(int query_low, int query_high){
        if(query_high < nodeLeft || query_low > nodeRight){  //disjoint
            return identity;
        }
        else if(query_low <= nodeLeft && query_high >= nodeRight  ){  // complete cover
            return nodeMin;
        }
        else{
            return min(leftChild -> rangeSum(query_low, query_high), rightChild -> rangeSum(query_low , query_high));
        }
    }
};

int main(){
    vector<ll> arr = {10, 15, 1, 5, 7, 9, 10, 20, 120};
    ll n = arr.size();

    //Build the segment tree
    MinSegmentTree segTree(0ll, n - 1, arr); 

    //Perform range query
    cout << "Min from 1 to 5: " << segTree.rangeSum(1, 5) << "\n";
    cout << "Sum from 0 to 3: " << segTree.rangeSum(0, 3) << "\n";

    cout << "\n";
    //pointupdate
    segTree.pointUpdate(2, 100);

    //Perform range query
    cout << "Sum from 1 to 5: " << segTree.rangeSum(1, 5) << "\n";
    cout << "Sum from 0 to 3: " << segTree.rangeSum(0, 3) << "\n";    
}