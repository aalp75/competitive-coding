#include <bits/stdc++.h>

using namespace std;

/**
 * mod int generaric class
 * 
 * MOD needs to be a prime number so every number has an inverse modulo MOD
 * 
 * ModInt<998244353> x = 3;
 * 
 * using mint = ModInt<998244353>
 * mint x = 3;
 */

template <long long MOD>
struct ModInt {

    long long val;

    ModInt() : val(0) {}

    ModInt(long long val_) : val(val_ % MOD) {}

    // unary
    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt(MOD - val * (val != 0));
    }

    // in-place ops
    friend ModInt operator+(ModInt a, const ModInt& b) {
        return a += b;
    }
    
    friend ModInt operator-(ModInt a, const ModInt& b) {
        return a -= b; 
    }
    friend ModInt operator*(ModInt a, const ModInt& b) { 
        return a *= b; 
    }

    friend ModInt operator/(ModInt a, const ModInt& b) { 
        return a /= b;
    }
    


};


int main() {
    using mint = ModInt<998244353>;
    mint x = 3;

    cout << x.val << '\n';
}