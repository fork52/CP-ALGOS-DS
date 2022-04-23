#include<bits/stdc++.h>
using namespace std;
using ll = long long;

/*
    Reference problem : https://codeforces.com/contest/300/problem/C
*/


/*
    Solution format for extended euclidean algorithm.
    Given two numbers A and B, the algorithm returns three integers g, x, y
    such that
    A * x + B * y = g    .. Where g = gcd(A, B)
*/
struct euclidean_solution{
    ll g, x, y;
};
 

/*
    Reference: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
*/
euclidean_solution extended_euclidean(ll a, ll b){
    if(b == 0){
        return {a, 1, 0};
    }
 
    auto [g, x1, y1] = extended_euclidean(b, a % b);
    ll x = y1;
    ll y = x1 - (a / b) * y1;
    return {g, x, y};
}


/*
    Returns the modular inverse of num under MOD using extended euclidean algo.
    We apply extended euclidean algorithm with A = num and b = MOD.
    The coefficent 'x' is our modular inverse.
    Reference: https://cp-algorithms.com/algebra/module-inverse.html
*/
ll get_modular_inverse(ll num, ll MOD){
    auto [g, x, y] = extended_euclidean(num, MOD);

    if(x < 0) x += MOD;     // if x is negative, increase it.
    x %= MOD;
    return x;
}


/*-----------------------------------------------------------------------------------*/
/*----------------------------ALTERNATIVE WAY----------------------------------------*/

/*
    Computes a ^ b under mod m 
*/
ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

/*
    Returns the modular inverse of num under MOD using Fermat's little theorem.
    The modular inverse of num under mod 'MOD' is num ^ (MOD - 2) % MOD.
    Reference: https://cp-algorithms.com/algebra/module-inverse.html
*/
ll get_mod_inverse_fermat(ll num, ll MOD){
    ll inv = binpow(num, MOD - 2, MOD);
    return inv;
}
