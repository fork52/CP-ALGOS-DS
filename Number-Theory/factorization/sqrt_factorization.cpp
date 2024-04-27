#include <vector>
#include <array>
#include <utility>
#include <iostream>

using ll = long long;

template<typename T> 
void disp_vec(std::vector<T> &arr){
    for(int i = 0; i < arr.size() ; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}



/**
 * @snip-start
 * snip-name: sqrt_factorization
 * snip-prefix: sqrt_factorization
 * snip-description: Square_root_factorization
*/
/*
    Returns the prime factorization of a number in the form:
    (prime1, cnt1), (prime2, cnt2) ....
    Time Complexity: O(sqrt(n))
*/
std::vector<std::pair<ll, ll>> prime_factorization(ll n) {
    std::vector<std::pair<ll, ll>> factorization;

    ll cnt;
    for (ll d : {2, 3, 5}) {
        cnt = 0;
        while (n % d == 0) {
            cnt++;
            n /= d;
        }
        if(cnt) factorization.push_back({d, cnt});
    }
    static std::array<ll, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
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
    Returns the prime factorization of a number in the form of a std::vector.
    Time Complexity: O(sqrt(n))
*/
std::vector<ll> prime_factorization_simple(ll n) {
    std::vector<ll> factorization;
    for (ll d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    static std::array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
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


void display_factorization(ll num, std::vector<std::pair<ll, ll>>& factorization){
    std::cout << "Factors of " << num << " are: "; 
    for(auto [fact, cnt] : factorization){
        std::cout << "(" <<  fact << ", " << cnt << "), ";
    }
    std::cout << "\n";
}
// @snip-end

int main(){
    ll num = 220;

    std::vector<std::pair<ll, ll>> facts = prime_factorization(num);
    display_factorization(num, facts);

    std::vector<ll> facts2 = prime_factorization_simple(num);
    std::cout << "Factors of " << num << " are: "; 
    disp_vec(facts2);
}