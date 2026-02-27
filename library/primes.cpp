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

vector<int> spf(N, 1); // smallest prime factor

void prime_factor_sieve() {
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        spf[i] = i;
        for (int j = 2 * i; j < N; j += i) {
            is_prime[j] = false;
            if (spf[j] == 1) prime_fspfactors[j] = i;
        }
    }
}

/**
 * pre compute all divisors of all numbers
 * 
 * Complexity is O(n log(n)) due to the harmonic series 
 * 
 * it's ok for N ~ 1e5 but a bit slow for N ~ 1e6 due to the lot of
 * push_back reallocation and bad cache locacity.
 * 
 * If constraints is up to 1e6, it's better to use another approach
 */

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