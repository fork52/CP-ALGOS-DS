#include <vector>
#include <numeric>
#include <iostream>

class LogFactorizer
{
    long long n;
    std::vector<long long> smallestPrimeFactor;

    void init()
    {
        this->smallestPrimeFactor.resize(n + 1);
        std::iota(smallestPrimeFactor.begin(), smallestPrimeFactor.end(), 0ll);

        for (long long i = 4; i <= n; i += 2)
        {
            smallestPrimeFactor[i] = 2;
        }

        for (long long i = 3; i * i <= n; i += 2)
        {
            if (smallestPrimeFactor[i] == i)
            {
                for (long long j = i * i; j <= n; j += i)
                {
                    smallestPrimeFactor[j] = i;
                }
            }
        }
    }

public:
    LogFactorizer(long long limit)
    {
        this->n = limit + 1;
        this->init();
    }

    std::vector<long long> factorize(long long x)
    {
        std::vector<long long> primeFactors;
        while (x > 1)
        {
            primeFactors.push_back(this->smallestPrimeFactor[x]);
            x = x / this->smallestPrimeFactor[x];
        }
        return primeFactors;
    }

    bool isPrime(long long x){
        return (x != 1) && (this->smallestPrimeFactor[x] == x);
    }
};


// int main(){
//     Factorizer obj(10);
//     std::vector<long long> facts = obj.factorize(10);
//     for(auto a: facts) std::cout << a << " ";
// }