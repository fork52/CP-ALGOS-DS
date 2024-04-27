using ll = long long;

/**
 * @snip-start
 * snip-name: binpow
 * snip-prefix: binpow
 * snip-description: Binary exponentiation
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
// @snip-end