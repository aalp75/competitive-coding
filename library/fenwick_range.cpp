#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct FenwickTree {
    vector<T> bit; // binary indexed tree
    int n;

    FenwickTree(int n_) : n(n_){
        bit.resize(n + 1);
    }

    FenwickTree(vector<T> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            range_add(i, i, a[i]);
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
    vector<int> a {1, 2, 3, 4, 5, 6};
    int n = a.size();
    FenwickTree<int> fenwick(a);

    for (size_t i = 0; i < n; i++) {
        cout << "a[" << i << "] = " << fenwick.point_query(i) << '\n';
    }

    // add 2 to all a[i] such that i is in [0, 3]
    fenwick.range_add(0, 3, 2);

    for (size_t i = 0; i < n; i++) {
        cout << "a[" << i << "] = " << fenwick.point_query(i) << '\n';
    }
    return 0;
}