#include "generic_segTree_lazy_prop.cpp"

/******************Start of SumSegTree***************************************/
template <typename T>
class SumSegTree : public ISegmentTree<T>
{
    const static T identity = 0;

    /* Constructs a segment tree from the array passed*/
    SumSegTree(int nodeLeft, int nodeRight, const std::vector<T> &arr)
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
            this->leftChild = new SumSegTree<T>(nodeLeft, mid, arr);
            this->rightChild = new SumSegTree<T>(mid + 1, nodeRight, arr);
            this->recalculate();
        }
    }

    T combine(const T &a, const T &b)
    {
        return a + b;
    }
    void applyDeltaOnNode(const T delta)
    {
        int range = this->nodeRight - this->nodeLeft + 1;
        this->nodeValue += range * delta;
    }

    void applyDeltaOnLazy(const T delta)
    {
        this->lazy += delta;
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
    static SumSegTree<T> *create(const std::vector<T> &arr)
    {
        int n = arr.size();
        return new SumSegTree<T>(0, n - 1, arr);
    }
};
/******************End of SumSegTree************************************/

// int main(){
//     std::vector<int> arr = {1, 2, 3};
//     SumSegTree<long long> *segtree = SumSegTree<long long>::create(arr);
//     int a = 1;
//     a++;
// }
