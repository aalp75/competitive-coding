#include <bits/stdc++.h>

using namespace std;

/**
 * fenwick tree that supports range update and point query
 * 
 * defined as 0-indexed array
 * 
 * based on cp-algorithms
 * https://cp-algorithms.com/data_structures/fenwick.html
 */

template<typename T>
struct FenwickTree {
    vector<T> bit; // binary indexed tree
    int n;

    FenwickTree(int n_) : n(n_){
        bit.resize(n + 1);
    }

    FenwickTree(const vector<T>& v) : FenwickTree(v.size()) {
        for (size_t i = 0; i < v.size(); i++)
            range_add(i, i, v[i]);
    }

    void add(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    void range_add(int l, int r, T val) {
        if (l > r) return;
        add(l, val);
        add(r + 1, -val);
    }

    T point_query(int idx) {
        T ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
};

int main() {
    vector<int> v {1, 2, 3, 4, 5, 6};
    FenwickTree<int> fenwick(v);

    for (size_t i = 0; i < v.size(); i++) {
        cout << "v[" << i << "] = " << fenwick.point_query(i) << '\n';
    }

    // add 2 to all a[i] such that i is in [0, 3]
    cout << "update range" << '\n';
    fenwick.range_add(0, 3, 2);

    for (size_t i = 0; i < v.size(); i++) {
        cout << "v[" << i << "] = " << fenwick.point_query(i) << '\n';
    }
    return 0;
}