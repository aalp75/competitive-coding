#include <vector>
#include <map>
#include <iostream>
#include <cassert>

using namespace std;

/**
 * compute very large fibonnaci number modulo MOD using the 
 * fast matrix exponentiation
 */

long long MOD = 1e9 + 7;
template <typename T>
vector<vector<T>> matMultiply(const vector<vector<T>>& A, const vector<vector<T>>& B) {
    
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

map<long long, long long> F;

long long fibo(long long n) {
    
    if (n == 0) return 0;

    if (F.find(n) != F.end()) return F[n];

    vector<vector<long long>> F0 = {{1}, {0}};
    vector<vector<long long>> M = {{1, 1}, {1, 0}};

    M = matPower(M, n - 1);

    auto res = matMultiply(M, F0);

    F[n] = res[0][0];
    F[n - 1] = res[1][0];

    return res[0][0];
}

int main() {

    long long res = fibo(7);
    cout << "F(7) = " << res << '\n'; // 13

    res = fibo(2142134);
    cout << "F(2142134) = " << res << '\n'; // 405032499

}