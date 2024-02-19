#include <array>
#include <deque>
#include <string>
#include <vector>
#include <algorithm>
#include <random>


// ***********************START RABIN KARP ****************************************
const long long RABIN_KARP_N = 3;

std::vector<long long> rabin_mod = {
    100000007ll, 100000049ll, 100030001ll, 99999989ll, 99999847ll, 99991207ll
};

std::vector<long long> rabin_weight = {
    2297, 3109, 3119, 3617, 4111, 4463
};

class RabinKarp{
    long long binpow(long long a, long long b, long long RABIN_KARP_MOD) {
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

    void init(){
        if((int)rabin_weight.size() == RABIN_KARP_N)
            return;

        auto rd = std::random_device {}; 
        auto rng = std::default_random_engine { rd() };
        std::shuffle(rabin_mod.begin(), rabin_mod.end(), rng);
        std::shuffle(rabin_weight.begin(), rabin_weight.end(), rng);

        while(rabin_weight.size() > RABIN_KARP_N) rabin_weight.pop_back();
        while(rabin_mod.size() > RABIN_KARP_N) rabin_mod.pop_back();
    }

public:
    std::deque<long long> dq;
    std::array<long long, RABIN_KARP_N> hashes = {0ll, 0ll, 0ll};

    RabinKarp(){
        init();
    }

    RabinKarp(const std::string& text){
        RabinKarp();
        for(int i = 0; i < text.size(); i++){
            this->push_back(text[i]);
        }
    }

    void push_back(long long val){
        dq.push_back(val);
        for(int i = 0; i < RABIN_KARP_N; i++){
            hashes[i] = (hashes[i] * rabin_weight[i]) % rabin_mod[i];
            hashes[i] = (hashes[i] + val) % rabin_mod[i];
        }
    }

    long long pop_front(){
        if(dq.empty()) return -1;
        long long val = dq.front(); dq.pop_front();
        long long length = (long long)(dq.size());
        for(int i = 0; i < RABIN_KARP_N; i++){
            long long subtract = (val * binpow(rabin_weight[i], length, rabin_mod[i]));
            subtract %= rabin_mod[i];
            hashes[i] = (hashes[i] - subtract + rabin_mod[i]) % rabin_mod[i];
        }
        return val;
    }

    int size(){
        return (int)dq.size();
    }
};

// ***********************END RABIN KARP ****************************************
