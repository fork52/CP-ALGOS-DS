#include <array>
#include <deque>
#include <string>

// ***********************START RABIN KARP ****************************************
const long long RABIN_KARP_N = 3;

const long long PRIME_MOD_1 = 100000007ll;
const long long PRIME_MOD_2 = 100000049ll;
const long long PRIME_MOD_3 = 10000019ll;

const long long MUL1 = 401;
const long long MUL2 = 2129;
const long long MUL3 = 1009;

class RabinKarp{
    static long long binpow(long long a, long long b, long long RABIN_KARP_MOD) {
        a %= RABIN_KARP_MOD;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % RABIN_KARP_MOD;
            a = a * a % RABIN_KARP_MOD;
            b >>= 1;
        }
        return res;
    }


public:
    const static std::array<long long, RABIN_KARP_N> multipliers;
    const static std::array<long long, RABIN_KARP_N> primeMods;

    std::deque<long long> dq;
    std::array<long long, RABIN_KARP_N> hashes = {0ll, 0ll};

    RabinKarp(){}

    RabinKarp(const std::string& text){
        for(int i = 0; i < text.size(); i++){
            this->push_back(text[i]);
        }
    }

    void push_back(long long val){
        dq.push_back(val);
        for(int i = 0; i < RABIN_KARP_N; i++){
            hashes[i] = (hashes[i] * multipliers[i]) % primeMods[i];
            hashes[i] = (hashes[i] + val) % primeMods[i];
        }
    }

    long long pop_front(){
        if(dq.empty()) return -1;
        long long val = dq.front(); dq.pop_front();
        long long length = (long long)(dq.size());
        for(int i = 0; i < RABIN_KARP_N; i++){
            long long subtract = (val * binpow(multipliers[i], length, primeMods[i]));
            subtract %= primeMods[i];
            hashes[i] = (hashes[i] - subtract + primeMods[i]) % primeMods[i];
        }
        return val;
    }

    int size(){
        return (int)dq.size();
    }
};

const std::array<long long, RABIN_KARP_N> RabinKarp::multipliers = {MUL1, MUL2, MUL3};
const std::array<long long, RABIN_KARP_N> RabinKarp::primeMods = {PRIME_MOD_1, PRIME_MOD_2, PRIME_MOD_3};
// ***********************END RABIN KARP ****************************************
