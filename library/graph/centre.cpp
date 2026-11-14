#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/**
 * find the centres of a tree
 * 
 * a centre is defined as the node that minimize the
 *  maximum distance to every to other nodes in the tree
 * 
 * It lies on the diameter and it's at the middle of the diameter
 * 
 * properties: 
 * 1) - if the diameter is even there is 1 centre 
 *    - if the diameter is odd  there are 2 centres
 * 
 * 2) all paths with a distance equal to the diameter pass through the centres
 */

pair<int, vector<int>> findCentres(vector<vector<int>>& adj, int n) {

    int furthest = 0;
    int diam = 0;

    vector<int> par(n + 1);

    auto dfs = [&](auto&& dfs, int u, int p, int d) -> void {
        if (d > diam) {
            diam = d;
            furthest = u;
        }
        par[u] = p;
        for (auto v : adj[u]) {
            if (v == p) continue;
            dfs(dfs, v, u, d + 1);
        }
    };

    // run 2 dfs to find the diameter

    dfs(dfs, 1, 0, 0);
    diam = 0;
    dfs(dfs, furthest, 0, 0);

    // find the centres which is in the middle of a diameter path
    int centre = furthest;
    for (int i = 0; i < diam / 2; i++) {
        centre = par[centre];
    }

    vector<int> centres = {centre};
    if (diam % 2 == 1) {
        centres.push_back(par[centre]);
    }

    // return {diam, centres}
    return {diam, centres};
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges = {
        {1, 2}, {2, 3}, {2, 4}, {4, 5}
    };
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto res = findCentres(adj, n);
    // diam: 3 centres: 2, 4
    cout << "diam: " << res.first << " centres: " << res.second[0] << ", " << res.second[1] << '\n';
    

    n = 8;
    adj.clear(); adj.resize(n + 1);
    edges = { 
        {3, 2}, {5, 8}, {2, 7}, {8, 1}, {2, 8}, {1, 4}, {6, 5}
    };

    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    res = findCentres(adj, n);
    // diam: 4 centres: 8
    cout << "diam: " << res.first << " centres: " << res.second[0] << '\n';


}
