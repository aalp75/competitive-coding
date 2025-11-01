#include <bits/stdc++.h>

using namespace std;

/**
 * fenwick tree
 * 
 * defined as 0-indexed array
 * 
 * based on cp-algorithms
 * https://cp-algorithms.com/data_structures/fenwick.html
 */

template<typename T>
struct FenwickTree {
    vector<T> bit;  // binary indexed tree
    int n;

    FenwickTree(int n_) : n(n_) {
        bit.resize(n);
    }

    FenwickTree(const vector<T>& v) : FenwickTree(v.size()) {
        for (size_t i = 0; i < v.size(); i++)
            add(i, v[i]);
    }

    T sum(int r) {
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, T delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6};
    FenwickTree<int> fenwick(v);

    int s = fenwick.sum(0, 4);
    cout << "a[0] + ... + a[4] = " << s << '\n';
    
    // a[2] += 3
    fenwick.add(2, 3);

    s = fenwick.sum(0, 4);
    cout << "a[0] + ... + a[4] = " << s << '\n';

    return 0;
}