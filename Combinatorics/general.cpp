// ----------------------------Combinatorics Start -----------------
// CHANGE COMBMAX AS PER YOUR NEEDS. MIND THE CONSTRAINTS!!!
const long long COMBMAX = 1e5;
const long long COMBMOD = 1e9 + 7;
long long factorial[COMBMAX + 1] = {};
class Combinatorics{
public:
    
    /**
     * Initialise a general combinatorics instance.
     * @param n Number at max you want to factorize
     * @param COMBMOD Mod to be used for combinatorics.
    */
    Combinatorics(){
        factorial[0] = factorial[1] = 1;
        for(long long i = 2; i < COMBMAX; i++){
            factorial[i] = factorial[i - 1] * i;
            if(factorial[i] >= COMBMOD){
                factorial[i] %= COMBMOD;
            }
        }
    }


    static long long binpow(long long a, long long b, const long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }

    long long nCr(long long n, long long r){
        long long ans = (factorial[n] * inverse(factorial[r])) % COMBMOD;
        return (ans * inverse(factorial[n - r])) % COMBMOD;
    }

    long long nPr(long long n, long long r){
        long long ans = (factorial[n] * inverse(factorial[n - r])) % COMBMOD;
    }

    static long long inverse(long long x){
        return binpow(x, COMBMOD - 2, COMBMOD);
    }
};
// ----------------------------Combinatorics End -------------------