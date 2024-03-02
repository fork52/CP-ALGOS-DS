#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

/** Data types ********************************/
using ll = long long;
using vll = vector<long long>;
using vint = vector<int>;
template <class T>
using max_pq = priority_queue<T>;
template <class T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
/**********************************************/

/** Bit manipulation */
template <typename T>
inline T isBitSet(T n, T i) { return (n >> i) & 1; }
template <typename T>
inline T isPowerOf2(T n) { return n && !(n & (n - 1)); }
template <typename T>
inline T getLsb(T val) { return val & -val; }
template <typename T>
inline T unSetBit(T n, T i) { return n & ~(1 << i); }
template <typename T>
inline T setBit(T n, T i) { return n | (1 << i); }
template <typename T>
inline T flipBit(T n, T i) { return n ^ (1 << i); }
/************/

/** Number Theory ******************************************/
const ll MOD = 1e9 + 7;
inline ll lcm(ll a, ll b) { return (a / __gcd(a, b) * b); }
/**********************************************************/

template <typename T>
class PrefixSum
{
    int n;
    vector<T> pre;

public:
    PrefixSum(const vector<T> &arr)
    {
        n = arr.size();
        pre = arr;
        for (int i = 1; i < n; i++)
            pre[i] += pre[i - 1];
    }

    T query(int l, int r)
    {
        if (l > r)
            return 0;
        if (l == 0)
            return pre[r];
        return pre[r] - pre[l - 1];
    }
};

template <typename T>
vector<T> input_array(const int n)
{
    vector<T> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    return arr;
}

template <typename T>
void disp_vec(const vector<T> &arr)
{
    for (auto &a : arr)
        cout << a << " ";
    cout << "\n";
}

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void preCompute()
{
    // Perform pre-computation
}


ll rescale(vector<pair<ll, ll>> &segs, ll m)
{
    ll n = segs.size();
    map<ll, ll> mapper;
    set<ll> nums;

    nums.insert(1);
    nums.insert(m);

    for (auto [s, e] : segs)
    {
        nums.insert(s);
        nums.insert(e);
    }

    int index = 1;
    for (auto x : nums)
    {
        mapper[x] = index;
        index++;
    }

    for (int i = 0; i < n; i++)
    {
        segs[i].first = mapper[segs[i].first];
        segs[i].second = mapper[segs[i].second];
    }

    return index;
}


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



void solve(int TC)
{
    ll n, m;
    cin >> n >> m;
    using pll = pair<ll, ll>;

    vector<pll> segs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> segs[i].first >> segs[i].second;
    }

    m = rescale(segs, m);

    // cout << "RescaledSize:" << m << "\n";

    vector<vector<pll>> endSegments(m + 2);
    std::sort(all(segs));

    ll sz = m + 5;
    vint arr(sz, 0);
    auto combine = [](int a, int b)
    {
        return min(a, b);
    };
    SegmentTreeWrapper<int> s(arr, combine, 1e7);    // SegmentTree *lz = Se
    ll best = 0;

    for (int i = 1, j = 0; i <= m - 1; i++)
    {
        // Add new segments
        while (j < n && segs[j].first <= i)
        {
            auto [l, r] = segs[j];
            // cout << "Adding" << " " << l << ", " << r << "\n";
            s.rangeUpdate(l, r, 1);
            endSegments[r].push_back(segs[j]);
            j++;
        }

        for (auto [l, r] : endSegments[i - 1])
        {
            s.rangeUpdate(l, r, -1);
        }

        ll mx = s.rangeQuery(i, i);
        ll mn = s.rangeQuery(1, m - 1);
        best = max(mx - mn, best);
    }

    cout << best << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(12) << fixed;

    ll TC, test_cases = 1;

    preCompute();

    cin >> test_cases;
    for (int TC = 1; TC <= test_cases; TC++)
    {
        solve(TC);
    }
}