#include <bits/stdc++.h>

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


int main() {
    return 0;
}