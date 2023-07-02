#include<bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T> 
void disp_vec(vector<T> &arr){
    for(int i = 0; i < arr.size() ; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

/*
    Returns the prime factorization of a number in the form:
    (prime1, cnt1), (prime2, cnt2) ....
*/
vector<pair<ll, ll>> prime_factorization(ll n) {
    vector<pair<ll, ll>> factorization;

    ll cnt;
    for (ll d : {2, 3, 5}) {
        cnt = 0;
        while (n % d == 0) {
            cnt++;
            n /= d;
        }
        if(cnt) factorization.push_back({d, cnt});
    }
    static array<ll, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (ll d = 7; d * d <= n; d += increments[i++]) {
        cnt = 0;
        while (n % d == 0) {
            cnt++;
            n /= d;
        }
        if(cnt) factorization.push_back({d, cnt});

        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back({n, 1});
    return factorization;
}


/*
    Returns the prime factorization of a number in the form of a vector.
*/
vector<ll> prime_factorization_simple(ll n) {
    vector<ll> factorization;
    for (ll d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (ll d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}


void display_factorization(ll num, vector<pair<ll, ll>>& factorization){
    cout << "Factors of " << num << " are: "; 
    for(auto [fact, cnt] : factorization){
        cout << "(" <<  fact << ", " << cnt << "), ";
    }
    cout << "\n";
}


int main(){
    ll num = 220;

    vector<pair<ll, ll>> facts = prime_factorization(num);
    display_factorization(num, facts);

    vector<ll> facts2 = prime_factorization_simple(num);
    cout << "Factors of " << num << " are: "; 
    disp_vec(facts2);
}