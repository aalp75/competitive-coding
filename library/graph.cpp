#include <bits/stdc++.h>

#include "../debug.h"

using namespace std;

/**
 * Floyd–Warshall algorithm
 * 
 * Computes the shortest paths for all pairs (i, j) in a directed or undirected graph
 * It works with negative edge weights as long as there is no negative cycle
 * 
 * The graph is represented as an n × n matrix where adj[i][j] is the weight
 * of the edge from i to j, or INF if there is no edge
 * 
 * dist[i][j][k] = shortest path from i to j using only {1, ..., k} as intermediate nodes
 * dist[i][j][k] = min(dist[i][j][k - 1], dist[i][k][k - 1] + dist[k][j][k - 1])
 * 
 * Time complexity is O(n^3), where n is the number of nodes
 * 
 * Implementation below uses nodes numbered from 1 to n
 */

vector<vector<int>> floyd_warshall(const vector<vector<int>>& adj, int n) {

    const int INF = 1e9;

    vector<vector<int>> dist(n + 1, vector<int> (n + 1, INF));

    // initialization
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j] != INF) dist[i][j] = adj[i][j];
        }
    }

    // computation
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    // dist[i][j] = shortest distance from i to j
    return dist;
}

/**
 * Finding the cycle in a Namori graph (a connected graph with N vertices and N edges).
 *
 * Such a graph contains exactly one simple cycle, because it has one more edge
 * than a tree
 *
 * Its structure can be seen as:
 *   - one simple cycle
 *   - trees (possibly empty) attached to vertices of the cycle
 *
 * The cycle can be identified by repeatedly removing all vertices of degree 1.
 * After all leaves are removed, the remaining vertices are exactly those belonging 
 * to the unique cycle.
 * 
 * Graph is 1-indexed: vertices are 1, 2, ..., n and edges.size() == n
 * 
 * Returns a vector<bool> of length n + 1 where onCycle[node] == true
 * if and only if the node is on the cycle
 * 
 * Complexity is O(N)
 */

vector<bool> findCycleNamori(vector<pair<int, int>>& edges, int n) {
    vector<int> deg(n + 1, 0);
    vector<vector<int>> adj(n + 1);

    for (auto [u, v] : edges) {
        deg[u]++; deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<int> q; // all nodes of degree 1
    vector<bool> onCycle(n + 1, true);

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) q.push(i);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        onCycle[node] = false;

        for (int neigh : adj[node]) {
            if (!onCycle[neigh]) continue; // already removed
            deg[neigh]--;
            if (deg[neigh] == 1) q.push(neigh);
        }
    }
    return onCycle;
}

/**
 * Finding a cycle in a directed connected graph
 *
 * Parent DSU approach
 * 
 * Complexity is O(M) where M is the number of edges
 * 
 * Graph is 1-indexed: vertices are 1, 2, ..., n
 * 
 * If the graph contains at least 1 cycle, it returns 
 * a vector consisting of all nodes in a given cycle
 * 
 * Can return a set instead to check if the node is on the given cycle
 */

vector<int> findCycleDirected(vector<vector<int>>& adj, int n) {
    vector<int> parent(n + 1, -1);
    vector<int> color(n + 1, 0);
    
    int cycle_start, cycle_end;

    auto dfs = [&](auto&& dfs, int node) -> bool {
        color[node] = 1;
        for (int neigh : adj[node]) {
            if (color[neigh] == 0) {
                parent[neigh] = node;
                if (dfs(dfs, neigh))
                    return true;
            }
            else if (color[neigh] == 1) {
                cycle_end = node;
                cycle_start = neigh;
                return true;
            }
        }
        color[node] = 2;
        return false;
    };

    for (int node = 1; node <= n; node++) {
        if (color[node] == 0 && dfs(dfs, node)) {
            break; // cycle found
        }
    }

    if (cycle_start == -1) { // acyclic
        return {};
    }
    
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int node = cycle_end; node != cycle_start; node = parent[node]) {
        cycle.push_back(node);
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

/**
 * Same algorithm than above but for an undirected connected graph
 */

vector<int> findCycle(vector<vector<int>>& adj, int n) {
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    
    int cycle_start, cycle_end;

    auto dfs = [&](auto&& dfs, int node, int par) -> bool {
        visited[node] = true;
        for (int neigh : adj[node]) {
            if (neigh == par) continue;
            if (visited[neigh]) {
                cycle_end = node;
                cycle_start = neigh;
                return true;
            }
            parent[neigh] = node;
            if (dfs(dfs, neigh, parent[neigh])) {
                return true;
            }
        }
        return false;
    };

    for (int node = 1; node <= n; node++) {
        if (!visited[node] && dfs(dfs, node, parent[node])) {
            break; // cycle found
        }
    }

    if (cycle_start == -1) { // acyclic
        return {};
    }
    
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int node = cycle_end; node != cycle_start; node = parent[node]) {
        cycle.push_back(node);
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

int main() {
    int n = 6;
    int m = 6;

    vector<pair<int, int>> edges = {
        {6, 3}, {3, 4}, {4, 5}, {5, 2}, {2, 3}, {2, 1}
    };

    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto cycle = findCycle(adj, n); // 5 4 3 2
    for (auto node : cycle) {
        cout << node << " ";
    }
    cout << '\n';

    return 0;
}