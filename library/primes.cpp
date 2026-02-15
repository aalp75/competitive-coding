#include <bits/stdc++.h>

using namespace std;

/**
 * prime numbers related function
 */

/**
 * sieve related algorithms
 */

const int N = 1e5;
vector<int> primes;

void prime_sieve() {
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < N; j += i) {
            is_prime[j] = false;
        }
    }
}

vector<int> prime_factors(N, 1);

void prime_factor_sieve() {
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        prime_factors[i] = i;
        for (int j = 2 * i; j < N; j += i) {
            is_prime[j] = false;
            if (prime_factors[j] == 1) prime_factors[j] = i;
        }
    }
}

vector<vector<int>> divisors(N);

void divisor_sieve() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divisors[j].push_back(i);
        }
    }
}

int main() {
}