#include <vector>
#include <queue>
#include <set>

const int INF32 = 1e9 + 10;

using namespace std;


/**
 * find bridges of a graph
 * 
 * a bridge is is an edge of a graph whose deletion increases
 * the graph's number of connected components
 * 
 * cp-algorithms implementation
 * 
 * tin[v]: entry time for node v
 * low[v]: lowest possible time we can reach v other than with parent
 */

set<pair<int, int>> find_bridges(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n ,false);
    vector<int> tin(n, 0);
    vector<int> low(n, 0);
    int timer = 1;

    set<pair<int, int>> bridges;

    auto dfs = [&](int node, int parent, auto&& dfs) -> void {
        visited[node] = true;
        tin[node] = timer;
        low[node] = timer;
        timer++;
        // flag to handle multiple edges between node and parent
        bool parent_skipped = false; 
        for (int neigh : adj[node]) {
            if (neigh == parent && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[neigh]) {
                low[node] = min(low[node], tin[neigh]);
            }
            else {
                dfs(neigh, node, dfs);
                low[node] = min(low[node], low[neigh]);
                if (low[neigh] > tin[node]) {
                    bridges.insert(minmax({node, neigh}));
                }
            }
        }
    };

    dfs(1, -1, dfs);
    return bridges;
}