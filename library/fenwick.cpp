#include <bits/stdc++.h>

using namespace std;

// base on cp-algorithms
// https://cp-algorithms.com/data_structures/fenwick.html

template<typename T>
struct FenwickTree {
    vector<T> bit;  // binary indexed tree
    int n;

    FenwickTree(int n_) : n(n_) {
        bit.resize(n);
    }

    FenwickTree(vector<T> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
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
    vector<int> a {1, 2, 3, 4, 5, 6};
    int n = a.size();
    FenwickTree<int> fenwick(a);

    int s = fenwick.sum(0, 4);
    cout << "a[0] + ... + a[4] = " << s << '\n';
    
    // a[2] += 3
    fenwick.add(2, 3);

    s = fenwick.sum(0, 4);
    cout << "a[0] + ... + a[4] = " << s << '\n';

    return 0;
}