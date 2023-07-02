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

void display_factorization(ll num, vector<pair<ll, ll>>& factorization){
    cout << "Factors of " << num << " are: "; 
    for(auto [fact, cnt] : factorization){
        cout << "(" <<  fact << ", " << cnt << "), ";
    }
    cout << "\n";
}

/*
    Performs Prime Sieve in the constructor based on the max number you want to factorize.
    Time Complexity: O(sqrt(max_number) * log(sqrt(max_number)))
    Uses those primes for factorization.
*/
class Factorizer{
public:
    ll limit;
    vector<bool> prime;
    vector<int> prime_list;

    /*
        max_number is the 'max' number you want to factorize.
    */
    Factorizer(ll max_number){
        this -> limit = sqrt(max_number) + 1;
        bool_prime_sieve();
    }

    
    void bool_prime_sieve(){
        prime.resize(limit + 1);
        fill(prime.begin(), prime.end(), true);
        prime[0] = prime[1] = false;
        prime_list.push_back(2);
        for(int i = 4; i <= limit; i += 2){
            prime[i] = false;
        }

        for(int i = 3 ; i <= limit; i += 2){
            if(prime[i]){
                prime_list.push_back(i);
                for(int j = 2 * i; j <= limit ; j += i){
                    prime[j] = false;
                }
            }
        }
    }


    /*
        Returns the prime factorization of a number in the form of a vector.
    */
    vector<ll> prime_factorize_simple(ll n) {
        vector<ll> factorization;
        for (ll d : prime_list) {
            if (d * d > n)
                break;
            while (n % d == 0) {
                factorization.push_back(d);
                n /= d;
            }
        }
        if (n > 1)
            factorization.push_back(n);
        return factorization;
    }

    /*
        Returns the prime factorization of a number in the form:
        (prime1, cnt1), (prime2, cnt2) ....
    */
    vector<pair<ll, ll>> prime_factorize(ll n){
        vector<pair<ll, ll>> factorization;
        ll cnt;
        for (ll d : prime_list) {
            if (d * d > n)
                break;
            cnt = 0;
            while (n % d == 0) {
                cnt++;
                n /= d;
            }
            if(cnt) factorization.push_back({d, cnt});
        }

        if(n > 1) factorization.push_back({n, 1});
        return factorization;
    }

};


int main(){
    ll num = 1e9;
    Factorizer obj(1e9);
    vector<ll> facts = obj.prime_factorize_simple(num);
    vector<pair<ll, ll>> facts2 = obj.prime_factorize(num);

    cout << "Factors of " << num << " are: "; 
    disp_vec(facts);
    display_factorization(num, facts2);
} 
