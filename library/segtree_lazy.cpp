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
 * - compute f([l, r]): compute(1, 0, n - 1, l, r)
 * - update v[i] += x for i in [l, r]: update(1, 0, n - 1, l, r, x)
 */

template <typename T>
struct SegTreeLazy {
    vector<T> tree;
    vector<T> lazy;
    vector<bool> marked;
    int n;

    SegTreeLazy() : n(0) {}

    SegTreeLazy(int n_) : n(n_) {
        tree.resize(4 * n, T());
        lazy.resize(4 * n, T());
        marked.resize(4 * n, false);
    }

    SegTreeLazy(const vector<T>& v) : SegTreeLazy(v.size()) {
        build(v, 1, 0, n - 1);
    }

    inline T merge(const T& left, const T& right) {
        return left + right;
    }

    void build(const vector<T>& v, int node, int tl, int tr) {
        if (tl == tr) {
            tree[node] = v[tl];
        } 
        else {
            int tm = (tl + tr) / 2;
            build(v, 2 * node, tl, tm);
            build(v, 2 * node + 1, tm + 1, tr);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void push(int node, int tl, int tr) {
        if (marked[node]) {
            int tm = (tl + tr) / 2;
            
            // scaled by number of elements
            tree[2 * node] = merge(tree[2 * node], lazy[node] * (tm - tl + 1));
            lazy[2 * node] = merge(lazy[node], lazy[2 * node]);
            marked[2 * node] = true;

            tree[2 * node + 1] = merge(tree[2 * node + 1], lazy[node] * (tr - tm));
            lazy[2 * node + 1] = merge(lazy[node], lazy[2 * node + 1]);
            marked[2 * node + 1] = true;

            marked[node] = false;
            lazy[node] = T();
        }
    }

    void update(int node, int tl, int tr, int l, int r, T val) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            tree[node] += val * (tr - tl + 1); // scaled by numbers of elements
            lazy[node] += val;
            marked[node] = true;
        } 
        else {
            push(node, tl, tr);
            int tm = (tl + tr) / 2;
            update(2 * node, tl, tm, l, min(r, tm), val);
            update(2 * node + 1, tm + 1, tr, max(l, tm + 1), r, val);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T compute(int node, int tl, int tr, int l, int r) {
        if (l > r) {
            return T();
        }
        if (l == tl && tr == r) {
            return tree[node];
        }
        push(node, tl, tr);
        int tm = (tl + tr) / 2;
        return merge(compute(2 * node, tl, tm, l, min(r, tm)),
                     compute(2 * node + 1, tm + 1, tr, max(l, tm+1), r));
    }
};

int main() {

    vector<int> v{1, 2, 3, 4, 5};
    int n = v.size();
    SegTreeLazy segtree(v);

    // compute sum on interval [0, 4]
    int s = segtree.compute(1, 0, n - 1, 0, 4);
    cout << "s = " << s << '\n'; // expected 15

    // add 8 on all elements of interval [2, 3]
    segtree.update(1, 0, n - 1, 2, 3, 8);
    
    // compute sum on interval [0, 4]
    s = segtree.compute(1, 0, n - 1, 0, 4);
    cout << "s = " << s << '\n'; // expected 31

    return 0;
}