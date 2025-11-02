#include <bits/stdc++.h>

using namespace std;

/**
 * segment tree lazy propagation
 * 
 * defined as 0-indexed array
 * top to bottom approach
 * 
 * tl = tree left, tr = tree right, tm = tree mid
 * 
 * operations:
 * - compute(l, r) = compute(1, 0, n - 1, l, r)
 * - update(l, r, val) = update(1, 0, n - 1, l, r, val)
 */

template<typename T>
struct SegTreeLazy {
    vector<T> tree;
    vector<T> lazy;
    int n;

    SegTreeLazy(int n_) : n(n_) {
        tree.resize(4 * n, T());
        lazy.resize(4 * n, T());
    }

    SegTreeLazy(const vector<T>& v) : SegTreeLazy(v.size()) {
        build(v, 1, 0, n - 1);
    }

    inline T merge(const T& left, const T& right) {
        return left + right;
    }

    void build(const vector<T>& a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * v, tl, tm);
            build(a, 2 * v + 1, tm + 1, tr);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void push(int v, int tl, int tr) {
        int tm = (tl + tr) / 2;
        
        // scaled by number of elements
        tree[2 * v] = merge(tree[2 * v], lazy[v] * (tm - tl + 1));
        lazy[2 * v] = merge(lazy[v], lazy[2 * v]);
        tree[2 * v + 1] = merge(tree[2 * v + 1], lazy[v] * (tr - (tm + 1) + 1));
        lazy[2 * v + 1] = merge(lazy[v], lazy[2 * v + 1]);
        lazy[v] = T();
    }

    void update(int v, int tl, int tr, int l, int r, T add) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            tree[v] += add * (tr - tl + 1);
            lazy[v] += add;
        } 
        else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(2 * v, tl, tm, l, min(r, tm), add);
            update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    T compute(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return T();
        }
        if (l == tl && tr == r) {
            return tree[v];
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return merge(compute(2 * v, tl, tm, l, min(r, tm)),
                     compute(2 * v + 1, tm + 1, tr, max(l, tm+1), r));
    }
};

int main() {

    vector<int> v{1, 2, 3, 4, 5};
    int n = v.size();
    SegTreeLazy segtree(v);

    // compute sum on interval [0, 4]
    int s = segtree.compute(1, 0, n - 1, 0, 4);
    cout << "s = " << s << '\n';

    // add 8 on all elements of interval [2, 3]
    segtree.update(1, 0, n - 1, 2, 3, 8);
    
    // compute sum on interval [0, 4]
    s = segtree.compute(1, 0, n - 1, 0, 4);
    cout << "s = " << s << '\n';

    return 0;
}