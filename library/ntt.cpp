#include <bits/stdc++.h>

using namespace std;

const long long MOD = 998244353;

/**
 * 
 * Polynoms multiplication in integer space using NTT
 * 
 * Similar to FFT but works on the integer ring up to 2^23 (8e6)
 * 
 * see fft.cpp for more details 
 * 
 * Complexity: O(nlog(n)) where n is the degree of polynoms
 * 
 * Implementation based on https://cp-algorithms.com/algebra/fft.html
 */

// as of now, it only works for mod = 998244353
// to extend to any mod, the other attributes (root, root_1, root_pw)
// must be computed dynamically

// code is still a bit slow - there is lot of spaces for optimisation

struct NTT {

    long long mod = 998244353;
    long long root = 31;
    long long root_1 = 128805723;
    long long root_pw = 1 << 23;

    int NAIVE_TRESHOLD = 60;

    NTT(long long _mod) : mod(_mod) {}

    long long fast_exponentiation(long long base, long long exp) { // base ^ exp
        base %= MOD;
        long long res  = 1;
        while (exp > 0) {
            if (exp & 1) 
                res = res * base % mod;
            base = base * base % mod;
            exp /= 2;
        }
        return res;
    }

    long long inverse(const long long x) { // x ^ -1 based on Euclidean division
        return x <= 1 ? x : mod - (mod / x) * inverse(mod % x) % mod;
    }

    // NTT iterative algorithm
    template <typename T>
    void ntt(vector<T>& p, bool invert) {
        int n = p.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(p[i], p[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            int wlen = invert ? root_1 : root;
            for (int i = len; i < root_pw; i <<= 1)
                wlen = (int)(1LL * wlen * wlen % mod);

            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len / 2; j++) {
                    int u = p[i+j], v = (int)(1LL * p[i+j+len/2] * w % mod);
                    p[i+j] = u + v < mod ? u + v : u + v - mod;
                    p[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                    w = (int)(1LL * w * wlen % mod);
                }
            }
        }

        if (invert) {
            int n_1 = inverse(n);
            for (auto& x : p)
                x = (int)(1LL * x * n_1 % mod);
        }
    }

    template <typename T>
    vector<T> multiplyNaive(const vector<T>& p1, const vector<T>& p2) {
        int n = p1.size();
        int m = p2.size();
        vector<T> res(n + m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i + j] = (res[i + j] + 1LL * p1[i] * p2[j]) % MOD;
            }
        }
        return res;
    }

    template <typename T>
    vector<T> multiply(const vector<T>& p1, const vector<T>& p2) {
        if (p1.empty() || p2.empty()) return {};

        if (min(p1.size(), p2.size()) <= NAIVE_TRESHOLD) {
            return multiplyNaive(p1, p2);
        }

        auto cp1(p1);
        auto cp2(p2);

        // Ensure elements are within [0, MOD)
        for (auto& x : cp1) x = (x % MOD + MOD) % MOD;
        for (auto& x : cp2) x = (x % MOD + MOD) % MOD;

        // n is the smallest power of 2 greater than or equal to p1.size() + p2.size()
        int n = 1;
        while (n < p1.size() + p2.size()) n *= 2;

        cp1.resize(n, 0);
        cp2.resize(n, 0);

        // Compute Number Theoretic Transform for both p1 and p2
        ntt(cp1, false);
        ntt(cp2, false);

        vector<T> res(n);

        // Point-wise multiplication
        for (int i = 0; i < n; i++) {
            res[i] = (1LL * cp1[i] * cp2[i]) % mod;
        }

        // Inverse NTT
        ntt(res, true);

        int realSize = p1.size() + p2.size() - 1;
        res.resize(realSize);

        return res;
    }
};

template <typename T>
void printPolynom(vector<T>& p1) {
    int n = p1.size();
    for (int i = 0; i < n; i++) {
        cout << p1[i];
        if (i == 1) {
            cout << "x";
        }
        if (i > 1) {
            cout << "x^" << i;
        }
        if (i < n - 1) {
            cout << " + ";
        }
    }
    cout << '\n';
}

int main() {

    vector<long long> p1 = {12349, 21349, 42989, 5432}; // 1 + x + 2x^2
    vector<long long> p2 = {43218, 98234, 39089}; // 2 + 3x + 4x^2

    NTT ntt(MOD);
    ntt.NAIVE_TRESHOLD = 0; // force ntt multiplication

    auto res = ntt.multiplyNaive(p1, p2);

    printPolynom(res); // 2 + 5x + 11x^2 + 10x^3 + 8x^4

    vector<long long> p = {1, 1, 2, 4};

    ntt.ntt(p, true);
    // (8,0) (-1,-3) (-2,0) (-1,3) 
    for (auto e : p) {
        cout << e << " ";
    }
    cout << '\n';

    auto res2 = ntt.multiply(p1, p2);
    printPolynom(res2);

    cout << '\n';

    return 0;
}
