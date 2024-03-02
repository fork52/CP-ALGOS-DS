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
    int nodeLeft, nodeRight;
    SegmentTree *leftChild, *rightChild;
    T nodeValue, lazy;

    void propagate()
    {
        if (this->lazy != 0)
        {
            this->nodeValue += this->lazy;

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
    void recalculate(std::function<T(const T &a, const T &b)> &combine)
    {
        if (isLeaf())
            return;
        nodeValue = combine(leftChild->nodeValue, rightChild->nodeValue);
    }

public:
    /* Constructs a segment tree from the array passed*/
    SegmentTree(int nodeLeft, int nodeRight, const std::vector<T> &arr,
                std::function<T(const T &a, const T &b)> &combine)
    {
        this->nodeLeft = nodeLeft;
        this->nodeRight = nodeRight;
        this->leftChild = this->rightChild = nullptr;
        this->lazy = 0;

        if (isLeaf())
        {
            this->nodeValue = arr[nodeLeft];
        }
        else
        {
            int mid = (nodeRight - nodeLeft) / 2 + nodeLeft;
            this->leftChild = new SegmentTree(nodeLeft, mid, arr, combine);
            this->rightChild = new SegmentTree(mid + 1, nodeRight, arr, combine);
            this->recalculate(combine);
        }
    }

    void rangeUpdate(
        int query_low, int query_high, T delta, std::function<T(const T &a, const T &b)> &combine)
    {
        propagate();

        if (query_high < nodeLeft || query_low > nodeRight)
        { // disjoint
            return;
        }
        else if (query_low <= nodeLeft && nodeRight <= query_high)
        {
            // Complete cover
            this->nodeValue += delta;

            if (!isLeaf())
            {
                this->leftChild->lazy += delta;
                this->rightChild->lazy += delta;
            }
            return;
        }

        // Partial cover
        leftChild->rangeUpdate(query_low, query_high, delta, combine);
        rightChild->rangeUpdate(query_low, query_high, delta, combine);
        this->recalculate(combine);
    }

    T rangeQuery(int query_low, int query_high, T& identity, std::function<T(const T &a, const T &b)> &combine)
    {
        this->propagate();

        if (query_high < nodeLeft || query_low > nodeRight)
        { // disjoint
            return identity;
        }
        else if (query_low <= nodeLeft && nodeRight <= query_high)
        { // complete cover
            return nodeValue;
        }
        else
        {
            // Partial cover
            return combine(
                leftChild->rangeQuery(query_low, query_high, identity, combine),
                rightChild->rangeQuery(query_low, query_high, identity, combine));
        }
    }
};

template <typename T>
class SegmentTreeWrapper
{
    std::function<T(const T &a, const T &b)> combine;
    T identity;
    SegmentTree<T> *segTree;

public:
    SegmentTreeWrapper(
        const std::vector<T> &arr,
        std::function<T(const T &a, const T &b)> combine,
        T identity) : identity(identity), combine(combine)
    {
        int n = arr.size();
        segTree = new SegmentTree<T>(0, n - 1, arr, combine);
    }

    T rangeQuery(int l, int r){
        return segTree->rangeQuery(l, r, identity, combine);
    }

    void rangeUpdate(int l, int r, T delta){
        segTree->rangeUpdate(l, r, delta, combine);
    }
};

int main()
{
    std::vector<int> arr = {1, 2, 3};
    auto combine = [](int a, int b)
    {
        return a > b ? a : b;
    };
    SegmentTreeWrapper<int> s(arr, combine, 1e6);
    int ans = s.rangeQuery(0, 0);
    ans++;
}