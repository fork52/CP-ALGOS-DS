#include <bits/stdc++.h>
using namespace std;

// Reference: https://leetcode.com/problems/implement-trie-prefix-tree/

// Assumes that you only have lower-case Alphabets
class Trie
{
private:
    Trie *children[26] = {};
    bool isword = false;

public:
    Trie() {}

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Trie *cur = this;
        for (auto &l : word)
        {
            if (cur->children[l - 'a'] == nullptr)
            {
                cur->children[l - 'a'] = new Trie();
            }
            cur = cur->children[l - 'a'];
        }
        cur->isword = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Trie *cur = this;
        for (auto &l : word)
        {
            if (cur->children[l - 'a'] == nullptr)
            {
                return false;
            }
            cur = cur->children[l - 'a'];
        }
        return cur && cur->isword;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        Trie *cur = this;
        for (auto &l : prefix)
        {
            if (cur->children[l - 'a'] == nullptr)
            {
                return false;
            }
            cur = cur->children[l - 'a'];
        }
        return cur;
    }

    bool deleteWord(string &word, int index = 0)
    {
        if (index == word.length())
        {
            if (!this->isword)
                return false; // Word doesn't exist
            this->isword = false;
            return isEmptyNode();
        }

        int chIndex = word[index] - 'a';
        if (this->children[chIndex] == nullptr)
            return false; // Word doesn't exist

        bool canDelete = this->children[chIndex]->deleteWord(word, index + 1);
        if (canDelete)
        {
            delete this->children[chIndex];
            this->children[chIndex] = nullptr;
            return isEmptyNode() && !this->isword;
        }
        return false;
    }

    bool isEmptyNode()
    {
        for (int i = 0; i < 26; i++)
        {
            if (this->children[i])
                return false;
        }
        return true;
    }
};

/* Will work for all ascii strings */
// class Generic_Trie
// {

//     map<char, Generic_Trie *> children = {};
//     bool isword = false;

// public:
//     /** Initialize your data structure here. */
//     Generic_Trie() {}

//     /** Inserts a word into the trie. */
//     void insert(string word)
//     {
//         Generic_Trie *cur = this;
//         for (auto &l : word)
//         {
//             if (!cur->children.count(l - 'a'))
//             {
//                 cur->children[l - 'a'] = new Generic_Trie();
//             }
//             cur = cur->children[l - 'a'];
//         }
//         cur->isword = true;
//     }

//     /** Returns if the word is in the trie. */
//     bool search(string word)
//     {
//         Generic_Trie *cur = this;
//         for (auto &l : word)
//         {
//             if (!cur->children.count(l - 'a'))
//             {
//                 return false;
//             }
//             cur = cur->children[l - 'a'];
//         }
//         return cur && cur->isword;
//     }

//     /** Returns if there is any word in the trie that starts with the given prefix. */
//     bool startsWith(string prefix)
//     {
//         Generic_Trie *cur = this;
//         for (auto &l : prefix)
//         {
//             if (!cur->children.count(l - 'a'))
//             {
//                 return false;
//             }
//             cur = cur->children[l - 'a'];
//         }
//         return cur;
//     }
// };

int main()
{

    // Usage of the Trie
    Trie root = Trie();

    string apple = "a";
    string applet = "ab";
    root.insert(apple);
    root.insert(applet);

    cout << root.startsWith(apple) << endl;
    cout << root.startsWith(applet) << endl;

    root.deleteWord(apple, 0);

    cout << root.search(apple) << endl;
    cout << root.search(applet) << endl;
}