#include<bits/stdc++.h>
using namespace std;

/* sieve of eratosthenes */

/* Returns a vector of size n*/
vector<bool> bool_prime_sieve(int n){
    vector<bool> prime(n, true);
    prime[0] = prime[1] = false;
    for(int i = 4; i <= n ; i += 2){
        prime[i] = false;
    }

    for(int i = 3 ; i <= n ; i += 2){
        if(prime[i]){
            for(int j = 2 * i; j <= n ; j += i){
                prime[j] = false;
            }
        }
    }
    return prime;
}


/*
    Use bitsets
    Note that the size of the bitset should be
    same as what you define in the function.
    (Just for sanity)
*/
bitset<10005> bits_prime_sieve(int n){
    bitset<10005> prime;
    prime.set();
    prime[0] = prime[1] = 0;
    for(int i = 4; i <= n ; i += 2){
        prime[i] = 0;
    }

    for(int i = 3 ; i <= n ; i += 2){
        if(prime[i]){
            for(int j = 2 * i; j <= n ; j += i){
                prime[j] = 0;
            }
        }
    }
    return prime;
}



int main(){
    int n = 1000;

    vector<bool> prime = bool_prime_sieve(n);
    for(int i = 1; i <= n ; i++){
        if(prime[i]){
            cout << i << " ";
        }
    }

}