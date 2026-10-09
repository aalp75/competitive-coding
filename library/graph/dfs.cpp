#include <vector>

using namespace std;

/**
 * dfs
 */

const int N = 1e5;
vector<bool> visited(N, false);

void dfs(vector<vector<int>>& adj, int node) {
    if (visited[node]) return;
    visited[node] = true;
    for (auto neigh : adj[node]) {
        dfs(adj, neigh);
    }
}
