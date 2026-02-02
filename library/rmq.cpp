#include <bits/stdc++.h>

using namespace std;

/**
 * range minimum/maximum queries
 * 
 * sparseTable[i][j] = minimum on the range[j, j + 2 ^ i - 1]
 * 
 * complexity:
 *  - build in O(n log n)
 *  - query in O(1)
 * 
 * usage:
 *  - RMQ rmq(array)
 *  - rmq.compute(l, r): compute f on array[l, ..., r]
 * 
 * notes:
 *  - f can be min, max and gcd
 *  - log2_floor can be used instead of lg2 array and is actually faster 
 *    due to cache misses
 * 
 *  https://cp-algorithms.com/data_structures/sparse-table.html
 */

int log2_floor(unsigned long i) { 
    return std::bit_width(i) - 1;
}

struct RMQ {

    vector<vector<int>> sparseTable;
    vector<int> lg;
    int n, k;

    template<typename T>
    RMQ(vector<T>& array) : n(array.size()) {
        lg.resize(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        k = lg[n];
        sparseTable.resize(k + 1, vector<int> (n));
        for (int i = 0; i < n; i++) {
            sparseTable[0][i] = array[i];
        }

        for (int i = 1; i <= k; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                sparseTable[i][j] = f(sparseTable[i - 1][j], sparseTable[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int f(int x, int y) {
        return min(x, y);
    }

    int compute(int l, int r) {
        int length = r - l + 1;
        int index = lg[length];
        int res = f(sparseTable[index][l], sparseTable[index][r - (1 << index) + 1]);
        return res;
    }
};

int main() {
    vector<int> array = {1, 5, 4, 2, 3, 10, 3, 5, 6 ,7};
    RMQ rmq(array);

    int res = rmq.compute(1, 4);
    cout << res << '\n';
}