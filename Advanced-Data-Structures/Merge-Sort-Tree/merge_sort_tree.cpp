#include <algorithm>
#include <vector>

/**
 * Class representing Merge Sort Tree.
 * @note You can modify the query function as per your problem.
 */
template <typename T>
class MergeSortTree
{
    int left = -1, right = -1;
    MergeSortTree *leftChild, *rightChild;
    std::vector<T> nums;

    bool isLeaf()
    {
        return this->left == this->right;
    }

public:
    /**
     * Constructs a MergeSortTree node.
     * @param l Left Index Boundary
     * @param r Right Index Boundary
     * @param arr Array whose queries need to be answered
     */
    MergeSortTree(int l, int r, std::vector<T> &arr)
        : left(l), right(r), leftChild(nullptr), rightChild(nullptr)
    {
        if (this->isLeaf())
        {
            this->nums = {arr[l]};
        }
        else
        {
            T mid = (right - left) / 2 + left;
            this->leftChild = new MergeSortTree(l, mid, arr);
            this->rightChild = new MergeSortTree(mid + 1, r, arr);

            std::merge(
                leftChild->nums.begin(), leftChild->nums.end(),
                rightChild->nums.begin(), rightChild->nums.end(),
                std::back_inserter(this->nums));
        }
    }

    /**
     * Returns the count of elements with value between `[mn, mx]`
     * in the index range `[l, r]` in the wrapped array.
     * @param l Left Index Boundary
     * @param r Right Index Boundary
     * @param mn Minimum Value
     * @param mx Maximum Value
     * @returns Count of number of elements.
     * @note
     * Time Complexity: O(log2(n) * log2(mx - mn))
     */
    int query(const int l, const int r, T mn, T mx)
    {
        if (l <= left && right <= r)
        {
            return std::upper_bound(nums.begin(), nums.end(), mx) -
                   std::lower_bound(nums.begin(), nums.end(), mn);
        }
        else if (left > r || right < l)
        {
            return 0;
        }
        else
        {
            return leftChild->query(l, r, mn, mx) + rightChild->query(l, r, mn, mx);
        }
    }
};

// Usage
// int main(){
//     std::vector<int> arr = {10, 1, 5, 13, 20, 9, 3, 15, 16, 17, 18};
//     MergeSortTree<int> *obj = new MergeSortTree(0, arr.size() - 1, arr);
//     int res = obj -> query(0, 10, 0, 3);
// }