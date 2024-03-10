#include "generic_segTree_lazy_prop.cpp"

/******************Start of XorSegTree***************************************/
template <typename T>
class XorSegTree : public ISegmentTree<T>
{
    const static T identity = 0;

    /* Constructs a segment tree from the array passed*/
    XorSegTree(int nodeLeft, int nodeRight, const std::vector<T> &arr)
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
            this->leftChild = new XorSegTree<T>(nodeLeft, mid, arr);
            this->rightChild = new XorSegTree<T>(mid + 1, nodeRight, arr);
            this->recalculate();
        }
    }

    T combine(const T &a, const T &b)
    {
        return a ^ b;
    }
    
    void applyDeltaOnNode(const T delta)
    {
        int range = this->nodeRight - this->nodeLeft + 1;
        if(range & 1){
            this->nodeValue ^= delta;
        }
    }

    void applyDeltaOnLazy(const T delta)
    {
        this->lazy ^= delta;
    }

    T getNodeIdentity()
    {
        return identity;
    }

    T getLazyIdentity()
    {
        return 0;
    }

public:
    static XorSegTree<T> *create(const std::vector<T> &arr)
    {
        int n = arr.size();
        return new XorSegTree<T>(0, n - 1, arr);
    }
};
/******************End of XorSegTree************************************/

// int main(){
//     std::vector<int> arr = {1, 2, 3};
//     XorSegTree<long long> *segtree = XorSegTree<long long>::create(arr);
// }
