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
vector<vector<long long>> matMultiply(vector<vector<long long>> A, vector<vector<long long>> B) {
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

// fast exponentiation for matrix
vector<vector<long long>> matPower(vector<vector<long long>> A, long long power) {
    if (power == 1) return A;
    if (power % 2 == 1) {
        return matMultiply(A, matPower(A, power - 1));
    }
    vector<vector<long long>> A2 = matPower(A, power / 2);
    return matMultiply(A2, A2);
}


int main() {
}