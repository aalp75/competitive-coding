#include <bits/stdc++.h>

using namespace std;

/**
 * find bridges of a graph
 * 
 * a bridge is is an edge of a graph whose deletion increases
 * the graph's number of connected components
 * 
 * based cp-algorithms implementation
 * 
 * tin[v]: entry time for node v
 * low[v]: lowest possible time we can reach v other than with parent 
 *         i.e. using only back edges
 * 
 * If tin[node] < low[neigh] it means that "neigh" 
 * cannot reach higher than itself using back edges
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
        bool parent_skipped = false; // flag to handle multiple edges between node and parent
        for (int neigh : adj[node]) {
            if (neigh == parent && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[neigh]) { // back edge
                low[node] = min(low[node], tin[neigh]);
            }
            else {
                dfs(neigh, node, dfs);
                low[node] = min(low[node], low[neigh]);
                if (tin[node] < low[neigh]) {
                    bridges.insert(minmax({node, neigh}));
                }
            }
        }
    };

    dfs(1, -1, dfs);
    return bridges;
}

/**
 * find articulation points in a graph
 * 
 * an articulation point is a node of a graph whose deletion increases
 * the graph's number of connected components
 * 
 * based cp-algorithms implementation
 * 
 * tin[v]: entry time for node v
 * low[v]: lowest possible time we can reach v other than with parent
 * 
 * Contrary to bridges finding the condition is tin[node] <= low[neigh]
 * In other words; the higher "neigh" can reach using back edges is "node"
 */

set<int> find_articulation_points(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n ,false);
    vector<int> tin(n, 0);
    vector<int> low(n, 0);
    int timer = 1;

    set<int> points; // it's better to use a set because the algorithm can add multiple time the same node

    auto dfs = [&](int node, int parent, auto&& dfs) -> void {
        visited[node] = true;
        tin[node] = timer;
        low[node] = timer;
        timer++;
        int childrens = 0;
        
        bool parent_skipped = false; // flag to handle multiple edges between node and parent
        for (int neigh : adj[node]) {
            if (neigh == parent && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[neigh]) { // back edge
                low[node] = min(low[node], tin[neigh]);
            }
            else {
                dfs(neigh, node, dfs);
                low[node] = min(low[node], low[neigh]);
                if (low[neigh] >= tin[node] && parent != -1) {
                    points.insert(node);
                }
                childrens++;
            }
        }
        if (parent == -1 && childrens > 1) { // handle root differently
            points.insert(node);
        }
    };

    dfs(1, -1, dfs);
    return points;
}

int main() {
    return 0;
}
