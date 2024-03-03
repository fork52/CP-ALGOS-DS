#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

/*
References:
    https://youtu.be/QvgpIX4_vyA

Related Problems:
    https://cses.fi/problemset/task/1648/
*/

template <typename T>
class SegmentTree
{
public:
    int nodeLeft, nodeRight;
    SegmentTree *leftChild, *rightChild;
    T nodeValue, lazy;

    void propagate()
    {
        if (this->lazy != 0)
        {
            applyDelta(this->lazy);

            if (!this->isLeaf())
            {
                this->leftChild->lazy += this->lazy;
                this->rightChild->lazy += this->lazy;
            }

            this->lazy = 0;
        }
    }

    /* Returns if current node is a leaf*/
    bool isLeaf()
    {
        return this->nodeLeft == this->nodeRight;
    }

    /* Recalculates the min for current node using left and right child mins*/
    void recalculate()
    {
        if (isLeaf())
            return;
        nodeValue = combine(leftChild->nodeValue, rightChild->nodeValue);
    }

    virtual T combine(const T &a, const T &b) = 0;
    virtual void applyDelta(const T delta) = 0;
    virtual T getIdentity() = 0;

    void rangeUpdate(int query_low, int query_high, T delta)
    {
        propagate();

        if (query_high < nodeLeft || query_low > nodeRight)
        { // disjoint
            return;
        }
        else if (query_low <= nodeLeft && nodeRight <= query_high)
        {
            // Complete cover
            applyDelta(delta);

            if (!isLeaf())
            {
                this->leftChild->lazy += delta;
                this->rightChild->lazy += delta;
            }
            return;
        }

        // Partial cover
        leftChild->rangeUpdate(query_low, query_high, delta);
        rightChild->rangeUpdate(query_low, query_high, delta);
        this->recalculate();
    }

    T rangeQuery(int query_low, int query_high)
    {
        this->propagate();

        if (query_high < nodeLeft || query_low > nodeRight)
        { // disjoint
            return this->getIdentity();
        }
        else if (query_low <= nodeLeft && nodeRight <= query_high)
        { // complete cover
            return nodeValue;
        }
        else
        {
            // Partial cover
            return combine(
                leftChild->rangeQuery(query_low, query_high),
                rightChild->rangeQuery(query_low, query_high));
        }
    }
};



template <typename T>
class MinSegTree: public SegmentTree<T>
{
    /* Constructs a segment tree from the array passed*/
    MinSegTree(int nodeLeft, int nodeRight, const std::vector<T> &arr)
    {
        this->nodeLeft = nodeLeft;
        this->nodeRight = nodeRight;
        this->leftChild = this->rightChild = nullptr;
        this->lazy = 0;

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
public:
    static MinSegTree<T> *create(const std::vector<T> &arr, T identity)
    {
        int n = arr.size();
        return new MinSegTree<T>(0, n - 1, arr);
    }

    T combine(const T &a, const T &b){
        return std::min(a, b);
    }
    void applyDelta(const T delta){
        this->nodeValue += delta;
    }
    T getIdentity(){
        return (int)1e7;
    }
};

int main()
{
    std::vector<int> arr = {1, 2, 3};

}