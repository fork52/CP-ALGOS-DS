#include "generic_segTree_lazy_prop.cpp"

/******************Start of MinSegTree***************************************/
template <typename T>
class MinSegTree: public ISegmentTree<T>
{
    /* Constructs a segment tree from the array passed*/
    MinSegTree(int nodeLeft, int nodeRight, const std::vector<T> &arr)
    {
        this->nodeLeft = nodeLeft;
        this->nodeRight = nodeRight;
        this->leftChild = this->rightChild = nullptr;
        this->lazy = this->getLazyIdentity();
 
        if (this->isLeaf())
        {
            this->nodeValue = arr[nodeLeft];
        }
        else
        {
            int mid = (nodeRight - nodeLeft) / 2 + nodeLeft;
            this->leftChild = new MinSegTree(nodeLeft, mid, arr);
            this->rightChild = new MinSegTree(mid + 1, nodeRight, arr);
            this->recalculate();
        }
    }
 
    T combine(const T &a, const T &b){
        return std::min(a, b);
    }
    void applyDeltaOnNode(const T delta){
        this->nodeValue += delta;
    }
 
   void applyDeltaOnLazy(const T delta){
        this->lazy += delta;
   }
 
    T getNodeIdentity(){
        // Change this!
        return 10000000;
    }
 
    T getLazyIdentity(){
        return 0;
    }
 
public:
    static MinSegTree<T> *create(const std::vector<T> &arr)
    {
        int n = arr.size();
        return new MinSegTree<T>(0, n - 1, arr);
    }
};
/******************End of MinSegTree************************************/
 
// int main(){
//     std::vector<int> arr = {1, 2, 3};
//     SumSegTree<long long> *segtree = SumSegTree<long long>::create(arr);
//     int a = 1;
//     a++;
// }
