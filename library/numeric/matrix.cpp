#include <vector>
#include<cassert>
#include <iostream>

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
template <typename T>
vector<vector<T>> matMultiply(const vector<vector<T>>& A, 
                              const vector<vector<T>>& B) {
    
    assert(A[0].size() == B.size());

    int n = A.size();
    int m = B[0].size();
    int k = A[0].size();

    vector<vector<T>> C(n, vector<T> (m, 0));

    for (int i = 0; i < n; i++) {
        for (int l = 0; l < k; l++) {
            for (int j = 0; j < m; j++) {
                C[i][j] = (C[i][j] + A[i][l] * B[l][j]) % MOD;
            }
        }
    }
    return C;
}

/**
 * In case we are in the min-plus ring (also known as distance product)
 * 
 * the idendity matrix is: diagonal 0, others INF
 */
template <typename T>
vector<vector<T>> matIdentity(int n, T type=1) {
    vector<vector<T>> Id(n, vector<T> (n, 0));
    for (int i = 0; i < n; i++) {
        Id[i][i] = 1;
    }
    return Id;
}

// fast exponentiation for matrix (base must be square)
template <typename T>
vector<vector<T>> matPower(vector<vector<T>> base, long long power) {

    int n = base.size();
    int m = base[0].size();

    assert(n == m);
    assert(power >= 0);

    vector<vector<T>> res = matIdentity(n, static_cast<T>(1));

    while (power > 0) {
        if (power & 1) res = matMultiply(res, base);
        base = matMultiply(base, base);
        power /= 2;
    }
    return res;
}


int main() {
    vector<vector<long long>> A = {{1, 2}, {3, 4}};
    vector<vector<long long>> B = {{5, 6}, {7, 8}};

    auto res = matMultiply(A, matPower(B, 10)); // C = A * B ^ 10
    
    for (auto row : res) {
        for (auto e : row) {
            cout << e << "\t";
        }
        cout << '\n';
    }

    // 321895290	76971166	
    // 719279971	116938524   
    
}