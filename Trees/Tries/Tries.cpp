#include<bits/stdc++.h>

using namespace std;

// Reference: https://leetcode.com/problems/implement-trie-prefix-tree/

// Assumes that you only have lower-case Alphabets
class Trie{
    private:
        Trie * children[26] = {};
        bool isword = false;

    public:

        Trie(){}
        
        /** Inserts a word into the trie. */
        void insert(string word) {
            Trie *cur = this;
            for(auto &l : word){
                if(cur->children[l-'a'] == nullptr){
                    cur->children[l-'a'] = new Trie();
                }
                cur = cur->children[l-'a'];
            }
            cur->isword = true;
        }
        
        /** Returns if the word is in the trie. */
        bool search(string word) {
            Trie *cur = this;
            for(auto &l : word){
                if(cur->children[l-'a'] == nullptr){
                    return false;
                }
                cur = cur->children[l-'a'];
            }
            return cur && cur->isword;

        }
        
        /** Returns if there is any word in the trie that starts with the given prefix. */
        bool startsWith(string prefix) {
            Trie *cur = this;
            for(auto &l : prefix){
                if(cur->children[l-'a'] == nullptr){
                    return false;
                }
                cur = cur->children[l-'a'];
            }
            return cur;
        }
};

// Will work for all ascii strings
class Generic_Trie {

    map<char, Generic_Trie *> children = {};
    bool isword = false;

public:
    /** Initialize your data structure here. */
    Generic_Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Generic_Trie *cur = this;
        for(auto &l : word){
            if(!cur->children.count(l-'a')){
                  cur->children[l-'a'] = new Generic_Trie();
            }
            cur = cur->children[l-'a'];
        }
        cur->isword = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Generic_Trie *cur = this;
        for(auto &l : word){
            if(!cur->children.count(l-'a')){
                return false;
            }
            cur = cur->children[l-'a'];
        }
        return cur && cur->isword;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Generic_Trie *cur = this;
        for(auto &l : prefix){
            if(!cur->children.count(l-'a')){
                return false;
            }
            cur = cur->children[l-'a'];
        }
        return cur;
    }
};


int main(){

    //Usage of the Trie
    Generic_Trie root = Generic_Trie();
    // Trie root = Trie();

    root.insert("apple");

    cout << root.search("apple") << endl;
    cout << root.startsWith("app") << endl;
    cout << root.startsWith("apk") << endl;

}