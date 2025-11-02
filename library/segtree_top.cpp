#include <bits/stdc++.h>

using namespace std;

/**
 * segment tree
 * 
 * defined as 0-indexed array
 * top to bottom approach
 * 
 * operations:
 * - compute f([l, r]): compute(1, 0, n - 1, l, r)
 * - update v[i] = x: update(1, 0, n - 1, i, x)
 * 
 * based on cp-algorithms
 * https://cp-algorithms.com/data_structures/segment_tree.html
 */

template<typename T>
struct SegTreeTop {
    vector<T> tree;
    int n;

    SegTreeTop(int n_) : n(n_) {
        tree.resize(4 * n, T());
    }

    SegTreeTop(const vector<T>& v) : SegTreeTop(v.size()) {
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

    void update(int node, int tl, int tr, int pos, T val) {
        if (tl == tr) {
            tree[node] = val;
        } 
        else {
            // split [tl, tr] in [tl, tm] and [tm + 1, tr]
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(2 * node, tl, tm, pos, val);
            }
            else {
                update(2 * node + 1, tm + 1, tr, pos, val);
            }
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T compute(int node, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(compute(2 * node, tl, tm, l, min(r, tm)),
                     compute(2 * node + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

int main() {

    vector<int> v{1, 2, 3, 4, 5};
    int n = v.size();
    SegTreeTop segtree(v);

    int s = segtree.compute(1, 0, n - 1, 0, 3);
    cout << "s = " << s << '\n';

    segtree.update(1, 0, n - 1, 2, 8);

    s = segtree.compute(1, 0, n - 1, 0, 3);
    cout << "s = " << s << '\n';

    return 0;
}