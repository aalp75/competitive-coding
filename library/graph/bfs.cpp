#include <vector>
#include <queue>

const int INF32 = 1e9 + 10;

using namespace std;

/**
 * bfs
 */

const int N = 1e5;
vector<bool> visited(N, false);

vector<int> bfs(vector<vector<int>>& adj, int n, int node) {
    vector<int> dist(n + 1, INF32);
    queue<int> nodes;
    nodes.push(node);
    dist[node] = 0;
    visited[node] = true;
    while (!nodes.empty()) {
        int node = nodes.front();
        nodes.pop();
        for (auto neigh : adj[node]) {
            if (visited[neigh]) continue;
            visited[neigh] = true;
            dist[neigh] = 1 + dist[node];
            nodes.push(neigh);
        }
    }
    return dist;
}