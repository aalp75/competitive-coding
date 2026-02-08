#include <bits/stdc++.h>

using namespace std;

constexpr long long MOD = 998'244'353;

/**
 * Matrix library
 * 
 * notes:
 *  - order of the loops on matrix multiplication is chosen to be cache friendly,
 *    i.e. loop on the rows of A and B
 */

// return C = A x B: (n * m) = (n * k) * (k * m)
vector<vector<long long>> matMultiply(const vector<vector<long long>>& A, 
                                      const vector<vector<long long>>& B) {
    
    assert(A[0].size() == B.size());

    int n = A.size();
    int m = B[0].size();
    int k = A[0].size();

    vector<vector<long long>> C(n, vector<long long> (m, 0));

    for (int i = 0; i < n; i++) {
        for (int l = 0; l < k; l++) {
            for (int j = 0; j < m; j++) {
                C[i][j] = (C[i][j] + A[i][l] * B[l][j]) % MOD;
            }
        }
    }
    return C;
}

vector<vector<long long>> matIdentity(int n) {
    vector<vector<long long>> Id(n, vector<long long> (n, 0));
    for (int i = 0; i < n; i++) {
        Id[i][i] = 1;
    }
    return Id;
}

// fast exponentiation for matrix (base must be square)
vector<vector<long long>> matPower(vector<vector<long long>> base, long long power) {

    int n = base.size();
    int m = base[0].size();

    assert(n == m);
    assert(power >= 0);

    vector<vector<long long>> res = matIdentity(n);

    while (power > 0) {
        if (power & 1) res = matMultiply(res, base);
        base = matMultiply(base, base);
        power /= 2;
    }
    return res;
}


int main() {
}