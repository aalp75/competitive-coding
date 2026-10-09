#include <bits/stdc++.h>

const long long MOD = 7;

using namespace std;

/**
 * mod int generaric class
 * 
 * MOD needs to be a prime number so every number has an inverse modulo MOD
 * 
 * Usage:
 * 
 * using mint = ModInt<998244353>
 * mint x = 3;
 * 
 * ModInt<998244353> x = 3;
 * 
 */

template <long long MOD>
struct ModInt {

    long long val;

    ModInt() : val(0) {}

    ModInt(long long v) : val(v % MOD) {
        if (val < 0) val += MOD;
    }

    // unary operators
    ModInt operator+() const { return *this; }
    ModInt operator-() const { return ModInt((val == 0) ? 0 : MOD - val); }

    // in-place operators
    ModInt& operator+=(const ModInt& other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }

    ModInt& operator-=(const ModInt& other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt& other) {
        val = (long long)(__int128(val) * other.val % MOD);
        return *this;
    }

    ModInt& operator/=(const ModInt& other) { 
        return *this *= other.inverse(); 
    }

    // binary operators (friends)
    friend ModInt operator+(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) { return a /= b; }

    // allow operations with long long on the right
    friend ModInt operator+(ModInt a, long long b) { return a += ModInt(b); }
    friend ModInt operator-(ModInt a, long long b) { return a -= ModInt(b); }
    friend ModInt operator*(ModInt a, long long b) { return a *= ModInt(b); }
    friend ModInt operator/(ModInt a, long long b) { return a /= ModInt(b); }

    // allow operations with long long on the left
    friend ModInt operator+(long long a, ModInt b) { return ModInt(a) += b; }
    friend ModInt operator-(long long a, ModInt b) { return ModInt(a) -= b; }
    friend ModInt operator*(long long a, ModInt b) { return ModInt(a) *= b; }
    friend ModInt operator/(long long a, ModInt b) { return ModInt(a) /= b; }

    // comparison operators
    friend bool operator==(const ModInt& a, const ModInt& b) { return a.val == b.val; }
    friend bool operator!=(const ModInt& a, const ModInt& b) { return a.val != b.val; }
    friend bool operator<(const ModInt& a, const ModInt& b) { return a.val < b.val; }
    friend bool operator>(const ModInt& a, const ModInt& b) { return a.val > b.val; }
    friend bool operator<=(const ModInt& a, const ModInt& b) { return a.val <= b.val; }
    friend bool operator>=(const ModInt& a, const ModInt& b) { return a.val >= b.val; }

    // increment / decrement operators
    ModInt& operator++() { return *this += 1; }
    ModInt& operator--() { return *this -= 1; }

    ModInt operator++(int) {
        ModInt tmp = *this;
        ++*this;
        return tmp;
    }

    ModInt operator--(int) {
        ModInt tmp = *this;
        --*this;
        return tmp;
    }

    // inverse
    // x ^ -1 based on Euclidean division
    ModInt inverse() const { 
        long long x = val;
        assert(x != 0);
        if (x == 1) return 1;
        return ModInt(MOD - (MOD / x) * ModInt(MOD % x).inverse().val % MOD);
    }

    // fast exponentiation
    // this ^ exp
    ModInt power(long long exp) const { 
        ModInt base = *this;
        ModInt res = 1;
        while (exp > 0) {
            if (exp & 1) 
                res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }

    // I/O
    friend ostream& operator<<(ostream& os, const ModInt& x) { return os << x.val; }
    friend istream& operator>>(istream& is, ModInt& x) {
        long long v;
        is >> v;
        x = ModInt(v);
        return is;
    }

    // cast
    operator long long() const { return val; }

};

// to work with debug.h
template <long long M>
string to_string(const ModInt<M>& x) {
    return std::to_string(x.val);
}

using mint = ModInt<MOD>;

int main() {

    mint x = 3;
    mint y = 5;

    cout << "x = " << x << ", y = " << y << '\n';

    cout << "x + y = " << x + y << '\n';
    cout << "x - y = " << x - y << '\n';
    cout << "x * y = " << x * y << '\n';
    cout << "x / y = " << x / y << '\n';
}