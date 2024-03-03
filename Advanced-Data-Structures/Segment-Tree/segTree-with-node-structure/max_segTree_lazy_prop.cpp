#include "generic_segTree_lazy_prop.cpp"

/******************Start of MaxSegTree***************************************/
template <typename T>
class MaxSegTree: public ISegmentTree<T>
{
    /* Constructs a segment tree from the array passed*/
    MaxSegTree(int nodeLeft, int nodeRight, const std::vector<T> &arr)
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
            this->leftChild = new MaxSegTree(nodeLeft, mid, arr);
            this->rightChild = new MaxSegTree(mid + 1, nodeRight, arr);
            this->recalculate();
        }
    }
 
    T combine(const T &a, const T &b){
        return std::max(a, b);
    }
    void applyDeltaOnNode(const T delta){
        this->nodeValue += delta;
    }
 
   void applyDeltaOnLazy(const T delta){
        this->lazy += delta;
   }
 
    T getNodeIdentity(){
        // Change this!
        return -100000000;
    }
 
    T getLazyIdentity(){
        return 0;
    }
 
public:
    static MaxSegTree<T> *create(const std::vector<T> &arr)
    {
        int n = arr.size();
        return new MaxSegTree<T>(0, n - 1, arr);
    }
};
/******************End of MaxSegTree************************************/
 
// int main(){
//     std::vector<int> arr = {1, 2, 3};
//     MaxSegTree<long long> *segtree = MaxSegTree<long long>::create(arr);
//     int a = 1;
//     a++;
// }
