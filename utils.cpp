#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;
const int N = 1e3;
long long INF = 1e9;

/**
 * modular operation
 */

long long add(const long long& x, const long long& y) { // x + y
    return (x + y + MOD) % MOD; 
}

long long substract(const long long& x, const long long& y) { // x - y
    return(x - y + MOD) % MOD;
}

long long mul(const long long& x, const long long& y) { // x * y
    return (x * y) % MOD; 
}

long long inverse(const long long& x) { // 1 / x
    return x <= 1 ? x : MOD - (long long)(MOD / x) * inverse(MOD % x) % MOD; 
}

long long division(const long long& x, const long long& y) { // x / y
    return mul(x, inverse(y));
}

long long fast_exponentiation(const long long& x, const long long& y) { // x ^ y
    if (y == 0) return 1;
    if (y == 1) return x;
    if (y % 2 == 0) {
        return fast_exponentiation(mul(x, x), y / 2);
    }
    return mul(x, fast_exponentiation(x, y - 1));
}

/**
 * modular arithmetic
 */

long long gcd(const long long& x, const long long& y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

long long lcm(const long long& x, const long long& y) {
    return x / gcd(x, y) * y;
}

/**
 * polynomial hashing
 * 
 * MOD = 1e9 + 9 is recommended
 * base = 2 for binary string
 * base = 31 for lowercase characters string
 */

long long compute_hash(vector<int>& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (auto value : s) {
        hash_value = add(hash_value, mul(value, base_power));
        base_power = mul(base_power, base);
    }
    return hash_value;
}

long long compute_hash(const string& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (auto c : s) {
        long long value = c -'a' + 1;
        hash_value = add(hash_value, mul(value, base_power));
        base_power = mul(base_power, base);
    }
    return hash_value;
}

/**
 * dfs
 */

vector<bool> visited(N, false);

void dfs(vector<vector<int>>& adj, int node) {
    if (visited[node]) return;
    visited[node] = true;
    for (auto neigh : adj[node]) {
        dfs(adj, neigh);
    }
}

/**
 * Dijkstra
 * 
 * graph is define on 1-indexed array
 */

void dijkstra(vector<vector<pair<long, int>>>& adj, int initial_node, int n) {

    vector<bool> visited(n + 1, false);
    vector<long long> distance(n + 1, INF);

    priority_queue<pair<long long, int>> q;

    q.push({0, initial_node});
    distance[initial_node] = 0;

    while (!q.empty()) {
        int node = q.top().second; q.pop();
        if (visited[node]) continue;
        visited[node] = true;

        for (auto neigh : adj[node]) {
            int next = neigh.first;
            long long weight = neigh.second;
            if (distance[node] + weight < distance[next]) {
                distance[next] = distance[node] + weight;
                q.push({-distance[next], next});
            }
        }
    }
}

/**
 * segment tree
 */

vector<int> tree(N);
int n;

int compute(int a, int b) {
    a += n; b += n;
    int s = 0;
    while (a <= b) {
        if (a % 2 == 1) 
                s += tree[a++];
        if (b % 2 == 0) 
                s += tree[b--];
        a /= 2; b /= 2;
    }
    return s;
}

void update(int k, int x) {
    k += n;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2 * k] + tree[2 * k + 1];
    }
}

/**
 * 
 */

int main() {
    return 0;
}
