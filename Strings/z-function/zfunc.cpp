#include<bits/stdc++.h>
using namespace std;


template<typename T> 
void disp_vec(vector<T> &arr){
    for(int i = 0; i < arr.size() ; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}


/*
Reference Problem: https://leetcode.com/problems/sum-of-scores-of-built-strings/
*/

/*
The z-function of a string s of length n is an array of length n,
where z[i] is the longest common prefix between string s and the substring s[i:].

In other words, is the length of the longest string that is, 
at the same time, a prefix of and a prefix of the suffix of starting at.

Reference: https://cp-algorithms.com/string/z-function.html
*/
vector<long long> z_function(string s) {
    long long n = (long long) s.length();
    vector<long long> z(n);
    for (long long i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}


int main(){
    vector<long long> z = z_function("babab");
    disp_vec(z);
}