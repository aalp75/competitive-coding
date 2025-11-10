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
    if (y == 0ll) return x;
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

int main() {

    int g = mygcd(12, 15);
    cout << g << '\n';
    
    return 0;
}