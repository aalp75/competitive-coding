#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;
const int N = 1e3;
const long long INF = 1e9;

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
    return ((x % MOD) * (y % MOD)) % MOD;
}

long long inverse(const long long& x) { // x ^ -1 based on Euclidean division
    return x <= 1 ? x : MOD - (MOD / x) * inverse(MOD % x) % MOD;
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
 * precompute all factorial and inverse factorial to compute 
 * binomial coefficient modulo a prime number in O(1)
 */

vector<long long> fact(N + 1);
vector<long long> fact_inv(N + 1);

void precompute_fact() {
    fact[0] = fact_inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    fact_inv[N] = inverse(fact[N]);
    for (int i = N - 1; i >= 1; i--) {
        fact_inv[i] = fact_inv[i + 1] * (i + 1) % MOD;
    }
}

int binomial_coeff(int k, int n) {
    return fact[n] * (fact_inv[n - k] * fact_inv[k] % MOD) % MOD;
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
 * disjoint set union (dsu)
 */

vector<int> linker(N);
vector<int> length(N);

void initialize() {
    int n;
    for (int i = 1; i <= n; i++) linker[i] = i;
    for (int i = 1; i <= n; i++) length[i] = 1;
}

int find(int x) {
    while (x != linker[x]) 
        x = linker[x];
    return x;
}

bool same(int a, int b) {
    return find(a) == find(b);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (length[a] < length[b]) 
        swap(a,b);
    length[a] += length[b];
    linker[b] = a;
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

int compute(int left, int right) {
    left += n; right += n;
    int res = 0;
    while (left <= right) {
        if (left % 2 == 1) 
                res += tree[left++];
        if (right % 2 == 0) 
                res += tree[right--];
        left /= 2; right /= 2;
    }
    return res;
}

void update(int index, int val) {
    index += n;
    tree[index] += val;
    for (index /= 2; index >= 1; index /= 2) {
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }
}

/**
 * custom hash function to avoid to get hacked
 * based on http://xorshift.di.unimi.it/splitmix64.c
 * can be used in unordered_map: unordered_map<int, int, custom_hash>
 */

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

/**
 * 
 */

int main() {
    return 0;
}
