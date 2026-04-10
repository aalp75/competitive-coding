#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7; // usually a prime number

/**
 * modular operations
 */

long long mod(const long long x, const long long m) { // x % m
    return (x % m + m) % m;
}

long long add(const long long x, const long long y) { // x + y
    return (x + y + MOD) % MOD; 
}

long long substract(const long long x, const long long y) { // x - y
    return(x - y + MOD) % MOD;
}

long long mul(const long long x, const long long y) { // x * y
    return ((x % MOD) * (y % MOD)) % MOD;
}

/**
 * The inverse function only work when MOD is a prime number
 * 
 * For non prime modulo, use the inverse2 below function
 * based on the extended euclidean algorithm
 */

long long inverse(const long long x) { // x ^ -1 based on Euclidean division
    return x <= 1 ? x : MOD - (MOD / x) * inverse(MOD % x) % MOD;
}

long long division(const long long x, const long long y) { // x / y
    return mul(x, inverse(y));
}

long long fast_exponentiation(long long base, long long exp) { // base ^ exp
    base %= MOD;
    long long res  = 1;
    while (exp > 0) {
        if (exp & 1) 
            res = res * base % MOD;
        base = base * base % MOD;
        exp /= 2;
    }
    return res;
}

/**
 * modular arithmetic
 */

long long mygcd(const long long& x, const long long& y) {
    if (y == 0) return x;
    return mygcd(y, x % y);
}

long long lcm(const long long& x, const long long& y) {
    return x / gcd(x, y) * y;
}

pair<long long, long long> extgcd(long long a, long long b) {
    if (b == 0) return make_pair(1, 0);
    long long x, y;
    auto xy = extgcd(b, a % b);
    x = xy.second;
    y = xy.first - a / b * x;
    return make_pair(x, y);
}

long long inverse2(long long a, long long mod) {
    auto [x, y] = extgcd(a, mod);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

/**
 * precompute all factorial and inverse factorial to compute 
 * binomial coefficient modulo a prime number in O(1)
 */

const int N = 100;

vector<long long> fact(N + 1);
vector<long long> fact_inv(N + 1);

void precompute_fact() {
    fact[0] = fact_inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    fact_inv[N] = inverse(fact[N]);
    for (int i = N - 1; i >= 1; i--) {
        fact_inv[i] = fact_inv[i + 1] * (i + 1) % MOD;
    }
}

int binomial_coeff(int k, int n) {
    return fact[n] * (fact_inv[n - k] * fact_inv[k] % MOD) % MOD;
}

int main() {

    int g = mygcd(12, 15);
    cout << g << '\n'; // 3
    
    return 0;
}