#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Heavy-Light decomposition
 * 
 * It usually needs to be paired with a segment tree
 * 
 * Implementation is 1-indexed
 * 
 * Steps:
 *  1 - build the heavy/light edges using two dfs
 *  2 - build the segment tree
 * 
 * Notes: there is at most O(log(n)) chains because each light-edge reduce
 * the size of the subtree by at least a factor 2
 * 
 * Example of use:
 *  - query the max on paths of a tree
 *
 */

template<typename T>
struct SegTree {
    vector<T> tree;
    int n;

    SegTree() {}

    SegTree(int n_) : n(n_) {
        tree.resize(2 * n);
    }

    SegTree(const vector<T>& v) : SegTree(v.size()) {
        for (size_t i = 0; i < v.size(); i++) {
            update(i, v[i]);
        }
    }

    T merge(T left, T right) {
        return max(left, right);
    }

    T compute(int left, int right) {
        left += n; right += n;
        T res = 0;
        while (left <= right) {
            if (left % 2 == 1) {
                    res = merge(res, tree[left++]);
            }
            if (right % 2 == 0) {
                    res = merge(res, tree[right--]);
            }
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


struct HLD {

    vector<int> sz;
    vector<int> parent;
    vector<int> depth;
    vector<int> heavy;
    int n;

    vector<int> head;
    vector<int> pos;
    vector<int> base;
    int timer;

    SegTree<long long> segtree;

    HLD(vector<vector<int>>& adj, vector<int>& values) {
        n = adj.size();
        sz.resize(n);
        parent.resize(n);
        depth.resize(n);
        heavy.resize(n);

        int root = 1;

        dfs(adj, root, -1, 0);

        head.resize(n);
        pos.resize(n);
        base.resize(n);
        timer = 1;
        decompose(adj, values, root, root);

        segtree = SegTree<long long>(n);
        for (int i = 1; i <= n; i++) {
            segtree.update(i, base[i]);
        }

    }

    void dfs(vector<vector<int>>& adj, int u, int p, int d) {
        sz[u] = 1;
        parent[u] = p;
        depth[u] = d;
        int mxSz = 0;
        int heavyNode = -1;
        for (auto v : adj[u]) {
            if (v == p) continue;
            dfs(adj, v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > mxSz) {
                mxSz = sz[v];
                heavyNode = v;
            }
        }
        if (heavyNode != -1) {
            heavy[u] = heavyNode;
        }
    }

    void decompose(vector<vector<int>>& adj, vector<int>& values, int u, int h) {
        head[u] = h;
        pos[u] = timer++;
        base[pos[u]] = values[u];
        if (heavy[u] != 0) {
            decompose(adj, values, heavy[u], h);
        }

        for (auto v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(adj, values, v, v);
        }
    };

    void update(int node, int val) {
        segtree.update(pos[node], val);
    }

    int query(int a, int b) {
        long long res = 0;
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) {
                swap(a, b);
            }

            res = segtree.merge(res, segtree.compute(pos[head[a]], pos[a]));
            a = parent[head[a]];
        }

        if (depth[a] > depth[b]) {
            swap(a, b);
        }

        res = segtree.merge(res, segtree.compute(pos[a], pos[b]));
        return res;
    }
};

int main() {

    int n = 5;
    vector<pair<int, int>> edges = {{1, 2}, {1, 3}, {2, 4}, {2, 5}};
    vector<vector<int>> adj(n + 1);
    for (auto edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<int> values = {0, 2, 4, 1, 3, 3};

    HLD hld(adj, values);

    cout << hld.query(3, 5) << '\n'; // 4
    hld.update(2, 2);
    cout << hld.query(3, 5) << '\n'; // 3

    return 0;
}