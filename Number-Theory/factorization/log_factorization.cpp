#include <vector>
#include <numeric>
#include <iostream>

class LogFactorizer
{
public:
    int n;
    std::vector<long long> smallestPrimeFactor;

    void init()
    {
        this->smallestPrimeFactor.resize(n);
        std::iota(smallestPrimeFactor.begin(), smallestPrimeFactor.end(), 0ll);

        for (int i = 4; i <= n; i += 2)
        {
            smallestPrimeFactor[i] = 2;
        }

        for (int i = 3; i * i <= n; i += 2)
        {
            if (smallestPrimeFactor[i] == i)
            {
                for (int j = i * i; j <= n; j += i)
                {
                    smallestPrimeFactor[j] = i;
                }
            }
        }
    }


    LogFactorizer(int limit)
    {
        this->n = limit + 1;
        this->init();
    }

    std::vector<long long> factorize(int x)
    {
        std::vector<long long> primeFactors;
        while (x > 1)
        {
            primeFactors.push_back(this->smallestPrimeFactor[x]);
            x = x / this->smallestPrimeFactor[x];
        }
        return primeFactors;
    }
};

// int main(){
//     Factorizer obj(10);
//     std::vector<long long> facts = obj.factorize(10);
//     for(auto a: facts) std::cout << a << " ";
// }