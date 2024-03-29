#include <bits/stdc++.h>
using namespace std;

const int X_MAX = int(2e7) + 5;

vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;
vector<int8_t> unique_primes;

// Note: this sieve is O(n), but the constant factor is worse than the O(n log log n) sieve due to the multiplication.
void sieve(int maximum) {
    maximum = max(maximum, 1);
    smallest_factor.assign(maximum + 1, 0);
    prime.assign(maximum + 1, true);
    prime[0] = prime[1] = false;
    primes = {};
 
    for (int i = 2; i <= maximum; i += 2) {
        prime[i] = i == 2;
        smallest_factor[i] = 2;
    }
 
    for (int i = 3; i <= maximum; i += 2) {
        if (prime[i]) {
            smallest_factor[i] = i;
            primes.push_back(i);
        }
 
        for (int p : primes) {
            if (p > smallest_factor[i] || int64_t(i) * p > maximum)
                break;
 
            prime[i * p] = false;
            smallest_factor[i * p] = p;
        }
    }
 
    if (maximum >= 2)
        primes.insert(primes.begin(), 2);
 
    unique_primes.assign(maximum + 1, 0);
 
    for (int i = 2; i <= maximum; i++) {
        int p = smallest_factor[i];
        unique_primes[i] = unique_primes[i / p] + ((i / p) % p != 0);
    }
}

// Prime factorizes n in worst case O(sqrt n / log n). Requires having run `sieve` up to at least sqrt(n).
// If we've run `sieve` up to at least n, takes O(log n) time.
vector<pair<int64_t, int>> prime_factorize(int64_t n) {
    int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
    assert(1 <= n && n <= sieve_max * sieve_max);
    vector<pair<int64_t, int>> result;
 
    if (n <= sieve_max) {
        while (n != 1) {
            int64_t p = smallest_factor[n];
            int exponent = 0;
 
            do {
                n /= p;
                exponent++;
            } while (n % p == 0);
 
            result.emplace_back(p, exponent);
        }
 
        return result;
    }
 
    for (int64_t p : primes) {
        if (p * p > n)
            break;
 
        if (n % p == 0) {
            result.emplace_back(p, 0);
 
            do {
                n /= p;
                result.back().second++;
            } while (n % p == 0);
        }
    }
 
    if (n > 1)
        result.emplace_back(n, 1);
 
    return result;
}
 
vector<int64_t> generate_factors(const vector<pair<int64_t, int>> &prime_factors, bool sorted = false) {
    // See http://oeis.org/A066150 and http://oeis.org/A036451 for upper bounds on number of factors.
    static vector<int64_t> buffer;
    int product = 1;
 
    for (auto &pf : prime_factors)
        product *= pf.second + 1;
 
    vector<int64_t> factors = {1};
    factors.reserve(product);
 
    if (sorted)
        buffer.resize(product);
 
    for (auto &pf : prime_factors) {
        int64_t p = pf.first;
        int exponent = pf.second;
        int before_size = int(factors.size());
 
        for (int i = 0; i < exponent * before_size; i++)
            factors.push_back(factors[factors.size() - before_size] * p);
 
        if (sorted && factors[before_size - 1] > p)
            for (int section = before_size; section < int(factors.size()); section *= 2)
                for (int i = 0; i + section < int(factors.size()); i += 2 * section) {
                    int length = min(2 * section, int(factors.size()) - i);
                    merge(factors.begin() + i, factors.begin() + i + section,
                          factors.begin() + i + section, factors.begin() + i + length,
                          buffer.begin());
                    copy(buffer.begin(), buffer.begin() + length, factors.begin() + i);
                }
    }
 
    assert(int(factors.size()) == product);
    return factors;
}
