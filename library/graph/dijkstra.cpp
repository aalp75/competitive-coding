#include <vector>
#include <queue>

const int INF32 = 1e9 + 10;
const long long INF64 = 1e18 + 10;

using namespace std;

/**
 * Dijkstra
 * 
 * graph is define on 1-indexed array
 */

void dijkstra(vector<vector<pair<int, int>>>& adj, int initial_node, int n) {

    vector<bool> visited(n + 1, false);
    vector<long long> distance(n + 1, INF64);

    priority_queue<pair<long long, int>> pq;

    pq.push({0, initial_node});
    distance[initial_node] = 0;

    while (!pq.empty()) {
        int node = pq.top().second; pq.pop();
        if (visited[node]) continue;
        visited[node] = true;

        for (auto neigh : adj[node]) {
            int next = neigh.first;
            long long weight = neigh.second;
            if (distance[node] + weight < distance[next]) {
                distance[next] = distance[node] + weight;
                pq.push({-distance[next], next});
            }
        }
    }
}