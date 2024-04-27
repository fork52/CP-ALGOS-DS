#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>


/**
 * @snip-start
 * snip-name: LogFactorizer
 * snip-prefix: log_factorization
 * snip-description: Log Factorization
*/
class LogFactorizer
{
    long long n;
    std::vector<long long> smallestPrimeFactor;
    std::vector<long long> _primeFactors;
    std::vector<std::pair<long long, long long>> _divisors;

    void _findDivisors(long long i, long long num)
    {
        if (i == (long long)_divisors.size())
        {
            _primeFactors.push_back(num);
            return;
        }

        // Ignore
        _findDivisors(i + 1, num);

        // Take
        auto [prime_num, freq] = _divisors[i];
        for (int mul = 1; mul <= freq; mul++)
        {
            num *= prime_num;
            _findDivisors(i + 1, num);
        }
    }

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

    /*
       Returns the prime factorization of a number in the sorted order
   */
    std::vector<long long> factorize_simple(long long x)
    {
        std::vector<long long> primeFactors;
        while (x > 1)
        {
            primeFactors.push_back(this->smallestPrimeFactor[x]);
            x = x / this->smallestPrimeFactor[x];
        }
        return primeFactors;
    }

    /*
        Returns the prime factorization of a number in the form:
        (prime1, cnt1), (prime2, cnt2) ....
    */
    std::vector<std::pair<long long, long long>> prime_factorize(long long x)
    {
        std::vector<std::pair<long long, long long>> primeFactors;
        long long pre = -1;
        while (x > 1)
        {
            long long factor = this->smallestPrimeFactor[x];
            if(factor == pre){
                primeFactors.back().second += 1;
            }
            else{
                primeFactors.emplace_back(factor, 1);
            }
            pre = factor;
            x = x / factor;
        }
        return primeFactors;
    }

    bool isPrime(long long x)
    {
        return (x != 1) && (this->smallestPrimeFactor[x] == x);
    }

    std::vector<long long> getAllDivisors(long long x)
    {
        _divisors = this->prime_factorize(x);

        _findDivisors(0, 1);
        std::vector<long long> primeFactors = _primeFactors;
        std::sort(primeFactors.begin(), primeFactors.end());

        // Reset vectors
        _primeFactors.clear(); _divisors.clear();

        return primeFactors;
    }
};
// @snip-end


// int main(){
//     Factorizer obj(10);
//     std::vector<long long> facts = obj.factorize(10);
//     for(auto a: facts) std::cout << a << " ";
// }