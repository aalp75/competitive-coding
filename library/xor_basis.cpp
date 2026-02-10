#include <bits/stdc++.h>

using namespace std;

/**
 * 
 * XOR Basis class
 * 
 * dim is usually 60 to fit 60 bits numbers
 * basis[i] = vector that control the bit i
 */

struct XORBasis {

    int dim;
    vector<long long> basis;
    int sz; // size of basis

    XORBasis() : dim(60), sz(0) {
        basis.resize(dim, 0);
    }

    void insert(long long mask) {
        for (int i = dim - 1; i >= 0; i--) {
            if ((mask & (1ll << i)) == 0) continue;
            if (!basis[i]) {
                basis[i] = mask;
                sz++;
                return;
            }
            mask ^= basis[i];
        }
    }

    long long getMax() {
        long long res = 0;
        for (int i = dim - 1; i >= 0; i--) {
            if ((res & (1ll << i)) == 0) {
                res = res ^ basis[i];
            }
        }
        return res;
    }
};

int main() {

    XORBasis xb;
    xb.insert(27); 
    xb.insert(3); 
    xb.insert(129); 
    xb.insert(10065);

    cout << xb.getMax() << '\n'; // 10195
    
    return 0;
}