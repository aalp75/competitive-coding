#include <bits/stdc++.h>

using namespace std;

/**
 * Lowest common ancestor
 * 
 */

struct LCA {

    int n, l;
    vector<vector<int>> adj;

    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;
    vector<int> depth;

    LCA (int root, vector<vector<int>>& tree) : n(tree.size()), adj(tree) {
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
        dfs(root, root, 0);
    }

    void dfs(int u, int p, int d) {
        tin[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;

        for (int i = 1; i <= l; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (int v : adj[u]) {
            if (v != p)
                dfs(v, u, d + 1);
        }

        tout[u] = ++timer;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = l; i >= 0; i--) {
            if (!isAncestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
};

int main() {

    int n = 4;
    vector<vector<int>> adj(n + 1);
    
    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[2].push_back(4);
    adj[4].push_back(2);

    LCA lca(1, adj);

    int ancestor = lca.lca(3, 4);

    cout << "The LCA of 3 and 4 is " << ancestor << '\n';
    return 0;
}