#include<vector>
#include<algorithm>

/******************Start of GenericSegmentTree************************************/
template <typename T>
class ISegmentTree
{
protected:
    int nodeLeft, nodeRight;
    ISegmentTree *leftChild, *rightChild;
    T nodeValue, lazy;
 
    void propagate()
    {
        if (this->lazy != this->getLazyIdentity())
        {
            this->applyDeltaOnNode(this->lazy);
 
            if (!this->isLeaf())
            {
                this->leftChild->applyDeltaOnLazy(this->lazy);
                this->rightChild->applyDeltaOnLazy(this->lazy);
            }
 
            this->lazy = this->getLazyIdentity();
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
    virtual void applyDeltaOnNode(const T delta) = 0;
    virtual void applyDeltaOnLazy(const T delta) = 0;
 
    virtual T getNodeIdentity() = 0;
    virtual T getLazyIdentity() = 0;
 
public:
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
            this->applyDeltaOnNode(delta);
 
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
            return this->getNodeIdentity();
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
/******************End of GenericSegmentTree************************************/

