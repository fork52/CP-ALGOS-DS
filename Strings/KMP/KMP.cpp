#include <bits/stdc++.h>
using namespace std;
template<typename T>
/*
References:
    https://cp-algorithms.com/string/prefix-function.html

Relevant Problems:
    https://binarysearch.com/problems/Longest-Prefix-that-Is-a-Suffix
    https://binarysearch.com/problems/Find-a-Linked-List-in-a-Binary-Tree
    https://binarysearch.com/problems/Make-Palindrome-by-Adding-a-Suffix
*/


vector<T> input_array( int n ){
    vector<T> arr;
    T t;
    for (int i = 0; i < n; i++){
        cin >> t;
        arr.push_back(t);
    }
    return arr;
}

template<typename T> 
void disp_vec( vector<T> &arr){
    for(int i=0; i<arr.size() ; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}


/*
Returs array of length n which represents prefix function for string s.

The prefix function for this string s is defined as an array π of length n, 
where π[i] is the length of the longest proper prefix of the substring s[0…i] 
which is also a suffix of this substring. 

A proper prefix of a string is a prefix that is not equal to the string itself. 
By definition, π[0]=0.    


Time Complexity: O(n)
*/
vector<int> prefix_function(string s) {

    int n = s.size(), j;
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

/*
    Returns a vector<int> containing all the starting indices in
    `txt` such that txt[index: index + pattern_size] = pattern. Overlapping
    string matches are also considered.

    Time Complexity: O(n + m)

*/
vector<int> KMP(string txt, string pattern){
    int n = txt.size();
    int pattern_size = pattern.size();

    vector<int> pi = prefix_function(pattern);
    vector<int> match;
    
    int j = 0;
    for(int i = 0; i < n; i++){
        while (j > 0 && txt[i] != pattern[j])
            j = pi[j-1];

        if(txt[i] == pattern[j]) j++;

        if(j == pattern_size){
            match.push_back(i - pattern_size + 1 );
            j = pi[pattern_size - 1];
        }
    }
    return match;
}


/*
    Returns whether pattern is present in txt.
    Time Complexity: O(n + m)
*/
bool KMP_exists(string txt, string pattern){
    int n = txt.size();
    int pattern_size = pattern.size();

    vector<int> pi = prefix_function(pattern);
    vector<int> match;
    
    int j = 0;
    for(int i = 0; i < n; i++){
        while (j > 0 && txt[i] != pattern[j])
            j = pi[j-1];

        if(txt[i] == pattern[j]) j++;

        if(j == pattern_size){
            return true;
        }
    }
    return false;
}


int main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC , n , test_cases;
    int ans;

    string txt, pattern;

    cin >> test_cases;
    for(int TC=1 ; TC<=test_cases ; TC++){
        cin >> txt >> pattern;

        vector<int> matches = KMP(txt, pattern);
        disp_vec(matches);
    }

}