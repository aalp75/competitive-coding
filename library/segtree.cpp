#include <bits/stdc++.h>

using namespace std;

/**
 * segment tree
 * 
 * defined as 0-indexed array
 */

template<typename T>
struct SegTree {
    vector<T> tree;
    int n;

    SegTree(int n_) : n(n_) {
        tree.resize(2 * n);
    }

    SegTree(const vector<T>& v) : SegTree(v.size()) {
        for (size_t i = 0; i < v.size(); i++) {
            update(i, v[i]);
        }
    }

    T merge(T left, T right) {
        return left + right;
    }

    T compute(int left, int right) {
        left += n; right += n;
        T res = 0;
        while (left <= right) {
            if (left % 2 == 1) 
                    res = merge(res, tree[left++]);
            if (right % 2 == 0) 
                    res = merge(res, tree[right--]);
            left /= 2; right /= 2;
        }
        return res;
    }

    void update(int index, T val) {
        index += n;
        tree[index] = val;
        for (index /= 2; index >= 1; index /= 2) {
            tree[index] = merge(tree[2 * index], tree[2 * index + 1]);
        }
    }
};

int main() {

    vector<int> v{1, 2, 3, 4, 5};

    SegTree segtree(v);

    int s = segtree.compute(0, 3);
    cout << "s = " << s << '\n';

    segtree.update(2, 8);

    s = segtree.compute(0, 3);
    cout << "s = " << s << '\n';

    return 0;
}