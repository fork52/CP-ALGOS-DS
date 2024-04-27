#include <vector>
#include <complex>
#include <algorithm>

/**
 * @snip-start
 * snip-name: SieveFactorizer
 * snip-prefix: sieve_factorization
 * snip-description: Sieve Factorization
*/
class Factorizer
{
    std::vector<long long> _factors;
     std::vector<std::pair<long long, long long>> _divisors;

    void _findDivisors(long long i, long long num)
    {
        if (i == (long long)_divisors.size())
        {
            _factors.push_back(num);
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

public:
    long long limit;
    std::vector<bool> prime;
    std::vector<int> prime_list;

    /*
        max_number is the 'max' number you want to factorize.
    */
    Factorizer(long long max_number)
    {
        this->limit = std::sqrt(max_number) + 1;
        bool_prime_sieve();
    }

    void bool_prime_sieve()
    {
        prime.resize(limit + 1);
        fill(prime.begin(), prime.end(), true);
        prime[0] = prime[1] = false;
        prime_list.push_back(2);

        for (long long i = 4; i <= limit; i += 2)
        {
            prime[i] = false;
        }

        for (long long i = 3; i <= limit; i += 2)
        {
            if (prime[i])
            {
                prime_list.push_back(i);
                for (long long j = i * i; j <= limit; j += i)
                {
                    prime[j] = false;
                }
            }
        }
    }

    /*
        Returns the prime factorization of a number in the form of a vector.
    */
    std::vector<long long> prime_factorize_simple(long long n)
    {
        std::vector<long long> factorization;
        for (long long d : prime_list)
        {
            if (d * d > n)
                break;
            while (n % d == 0)
            {
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
    std::vector<std::pair<long long, long long>> prime_factorize(long long n)
    {
        std::vector<std::pair<long long, long long>> factorization;
        long long cnt;
        for (long long d : prime_list)
        {
            if (d * d > n)
                break;
            cnt = 0;
            while (n % d == 0)
            {
                cnt++;
                n /= d;
            }
            if (cnt)
                factorization.push_back({d, cnt});
        }

        if (n > 1)
            factorization.push_back({n, 1});
        return factorization;
    }

    /*
        Returns all divisors of a number including 1 and n
        in sorted order.
    */
    std::vector<long long> getAllDivisors(long long n)
    {
        _divisors = prime_factorize(n);
        _findDivisors(0, 1);

        std::vector<long long> factors = _factors;
        std::sort(factors.begin(), factors.end());

        // Reset vectors
        _factors.clear();
        _divisors.clear();

        return factors;
    }
};
// @snip-end

// int main(){
//     ll num = 1e9;
//     Factorizer obj(1e9);
//     vector<ll> facts = obj.prime_factorize_simple(num);
//     vector<pair<ll, ll>> facts2 = obj.prime_factorize(num);

//     cout << "Factors of " << num << " are: ";
//     disp_vec(facts);
//     display_factorization(num, facts2);
// }
