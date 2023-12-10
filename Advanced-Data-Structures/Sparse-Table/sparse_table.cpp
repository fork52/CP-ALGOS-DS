#include <vector>
#include <functional>

/**
 * Generic implementation of sparse table. Everything is 0-indexed!
 */
template <typename T>
class SparseTable
{
    T **sparseTable;
    int *lg, MAXN, LOGN;
    std::function<int(const T &a, const T &b)> f;

public:
    /**
     * Constructs a Sparse Table for querying the given array
     * @param arr vector to be queried.
     * @param func Is a idempotent function. Ex: min, max, gcd
     * @note TC: O(nlogn) SC: O(nlogn)
     */
    SparseTable(std::vector<T> &arr, std::function<int(const int &a, const int &b)> func)
        : f(func)
    {

        this->MAXN = arr.size();

        // Precompute logs
        lg = new int[MAXN + 1];
        lg[1] = 0;
        for (int i = 2; i <= MAXN; i++)
        {
            lg[i] = lg[i >> 1] + 1;
        }

        this->LOGN = lg[MAXN];

        sparseTable = new T *[MAXN];
        for (int i = 0; i < MAXN; i++)
        {
            sparseTable[i] = new T[LOGN + 1];
            sparseTable[i][0] = arr[i];
        }

        for (int j = 1; j <= LOGN; j++)
        {
            for (int i = 0; i + (1 << j) - 1 < MAXN; i++)
            {
                sparseTable[i][j] = f(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    /**
     * Answers query in the range `[L ,R]` inclusive.
     * @param L left boundary
     * @param R right boundary
     * @note Time Complexity : O(1)
     */
    T query(int L, int R)
    {
        int k = lg[R - L + 1];
        return f(sparseTable[L][k], sparseTable[R - (1 << k) + 1][k]);
    }

    ~SparseTable()
    {
        delete[] lg;
        for (int i = 0; i < MAXN; i++)
        {
            delete[] sparseTable[i];
            sparseTable[i] = nullptr;
        }
        delete[] sparseTable;
        sparseTable = (T **)nullptr;
        lg = nullptr;
    }
};

// int main(){
//     std::vector<int> arr = {1, 2, 3, 4};
//     SparseTable sparseTable(arr, [](int a, int b){
//         return a > b ? a : b;
//     });

//     for(int i = 0; i < arr.size(); i++){
//         for(int j = j; j < arr.size(); j++){
//             // assert()
//         }
//     }
// }