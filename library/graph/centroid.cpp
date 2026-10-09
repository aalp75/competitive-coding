#include <vector>
#include <queue>

const int INF32 = 1e9 + 10;

using namespace std;

/**
 * find centroids of a tree
 * 
 * 1 or 2 centroids maximum (Jordan theorhem)
 */

vector<int> find_centroids(vector<vector<int>>& adj, int n) {
    vector<int> centroids;
    vector<int> sz(n + 1, 0);
    vector<bool> is_centroid(n + 1, true);
    auto dfs = [&](int node, int parent, auto&& dfs) -> void {
        sz[node] = 1;
        for (auto neigh : adj[node]) {
            if (neigh == parent) continue;
            dfs(neigh, node, dfs);
            sz[node] += sz[neigh];
            if (sz[neigh] > n / 2) {
                is_centroid[node] = false;
            }
        }
        if (n - sz[node] > n / 2) {
            is_centroid[node] = false;
        }
        if (is_centroid[node]) {
            centroids.push_back(node);
        }
    };    

    dfs(1, -1, dfs);
    
    return centroids;
}
