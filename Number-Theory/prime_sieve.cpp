#include <vector>
#include <bitset>

/* Sieve of eratosthenes */

/* Returns a std::vector of size n*/
std::vector<bool> bool_prime_sieve(int n){
    std::vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for(int i = 4; i <= n ; i += 2){
        prime[i] = false;
    }

    for(int i = 3 ; i * i <= n ; i += 2){
        if(prime[i]){
            for(int j = i * i; j <= n ; j += i){
                prime[j] = false;
            }
        }
    }
    return prime;
}


/*
    Uses bitsets
    Note that the size of the bitset should be
    same as what you define in the function.
    (Just for sanity)
*/
std::bitset<100000> bits_prime_sieve(int n){
    std::bitset<100000> prime;
    prime.set();
    prime[0] = prime[1] = 0;
    for(int i = 4; i <= n ; i += 2){
        prime[i] = 0;
    }

    for(int i = 3 ; i * i <= n ; i += 2){
        if(prime[i]){
            for(int j = i * i; j <= n ; j += i){
                prime[j] = 0;
            }
        }
    }
    return prime;
}

// int main(){
//     int n = 1000;
//     std::vector<bool> prime = bool_prime_sieve(n);
//     for(int i = 1; i <= n ; i++){
//         if(prime[i]){
//             std::cout << i << " ";
//         }
//     }

// }