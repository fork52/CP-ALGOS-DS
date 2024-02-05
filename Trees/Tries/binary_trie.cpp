#include <algorithm>
#include <vector>

class Trie
{
    int isNum;
    std::vector<Trie *> children;

public:
    Trie()
    {
        children.resize(2);
        std::fill(children.begin(), children.end(), nullptr);
        isNum = 0;
    }

    void insert(int val)
    {
        int b;
        Trie *cur = this;
        for (int i = 30; i >= 0; i--)
        {
            b = (val >> i) & 1;

            if (cur->children[b] == nullptr)
            {
                cur->children[b] = new Trie();
            }

            cur = cur->children[b];
        }
    }

    int get_best_xor(int val)
    {
        int b, x = 0;
        Trie *cur = this;

        for (int i = 30; i >= 0; i--)
        {
            b = (val >> i) & 1;
            if (cur->children[b ^ 1] != nullptr)
            {
                cur = cur->children[b ^ 1];
                x |= (1 << i);
            }
            else
            {
                cur = cur->children[b];
            }
        }

        return x;
    }
};

/**
 *
 * USAGE EXAMPLE
 * **************************************
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie obj;
        for(auto value : nums){
            obj.insert(value);
        }

        int ans = 0;
        for(auto value : nums){
            ans = max(ans, obj.get_best_xor(value));
        }

        return ans;
    }
};
 * **/