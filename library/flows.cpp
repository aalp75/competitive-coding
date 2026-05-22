#include <bits/stdc++.h>

using namespace std;

const int INF32 = 1e9 + 10;

/**
 * Flow algorithms library
 */

/**
 * Maximum flow in a directed weighted graph using the Edmonds–Karp algorithm.
 *
 * Edmonds–Karp is an implementation of the Ford–Fulkerson method.
 * Ford–Fulkerson does not specify how to choose augmenting paths, while
 * Edmonds–Karp always chooses the shortest augmenting path in terms of
 * the number of edges, using BFS.
 *
 * It guarantees a time complexity of O(VE^2). At each iteration, at least
 * one new edge on the augmenting path becomes full.
 *
 * The graph is represented by:
 * - adj: an adjacency list containing both forward and reverse edges
 * - capacity: a matrix where capacity[u][v] is the remaining capacity from u to v
 *
 * Implementation based on https://cp-algorithms.com/graph/edmonds_karp.html
 */

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int, int>> q;
    q.push({s, INF32});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);

                if (next == t) {
                    return new_flow;
                }

                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);

    int new_flow;
    while ((new_flow = bfs(s, t, parent)) > 0) {
        flow += new_flow;

        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    n = 6;

    adj.resize(n);
    capacity.resize(n, vector<int>(n, 0));

    vector<vector<int>> edges = {
        // {u, v, w} represents a directed edge u --(w)--> v
        {0, 1, 4},
        {0, 2, 7},
        {1, 2, 3},
        {1, 3, 2},
        {2, 3, 3},
        {2, 4, 5},
        {3, 4, 3},
        {4, 5, 8},
        {3, 5, 5},
    };

    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        adj[u].push_back(v);
        adj[v].push_back(u); // reverse edge for the residual graph

        capacity[u][v] += w;
    }

    int source = 0;
    int sink = 5;

    int maxFlow = maxflow(source, sink);

    cout << "The maximum flow from " << source << " to " << sink << " is " << maxFlow << '\n'; // 10
}