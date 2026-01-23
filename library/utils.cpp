#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;
const int N = 1e3;
const long long INF32 = 1e9;
const long long INF64 = 1e18;
int n;

/**
 * common operation
 */

// return the ceil number of x / y e.g. ceil_division(5, 2) = 3
long long ceil_division(long long x, long long y) {
    long long res = x / y + (x % y != 0);
    return res;
}

/**
 * modular operation
 */

long long mod(const long long x, const long long m) { // x % m
    return (x % m + m) % m;
}

long long add(const long long x, const long long y) { // x + y
    return (x + y + MOD) % MOD; 
}

long long substract(const long long x, const long long y) { // x - y
    return(x - y + MOD) % MOD;
}

long long mul(const long long x, const long long y) { // x * y
    return ((x % MOD) * (y % MOD)) % MOD;
}

long long inverse(const long long x) { // x ^ -1 based on Euclidean division
    return x <= 1 ? x : MOD - (MOD / x) * inverse(MOD % x) % MOD;
}

long long division(const long long x, const long long y) { // x / y
    return mul(x, inverse(y));
}

long long fast_exponentiation(long long base, long long exp) { // base ^ exp
    base %= MOD;
    long long res  = 1;
    while (exp > 0) {
        if (exp & 1) 
            res = res * base % MOD;
        base = base * base % MOD;
        exp /= 2;
    }
    return res;
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
 * sieve related algorithms
 */

vector<int> primes;

void prime_sieve() {
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        for (int j = 2 * i; j < N; j += i) {
            is_prime[j] = false;
        }
    }
}

vector<int> prime_factors(N, 1);

void prime_factor_sieve() {
    vector<bool> is_prime(N, true);
    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        prime_factors[i] = i;
        for (int j = 2 * i; j < N; j += i) {
            is_prime[j] = false;
            if (prime_factors[j] == 1) prime_factors[j] = i;
        }
    }
}

vector<vector<int>> divisors(N);

void divisor_sieve() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divisors[j].push_back(i);
        }
    }
}

/**
 * polynomial hashing
 * 
 * MOD = 1e9 + 9 is recommended
 * base = 2 for binary string
 * base = 31 for lowercase characters string
 * 2 versions available: vector<int> and string
 */

long long compute_hash(vector<int>& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (int value : s) {
        hash_value = (hash_value + value* base_power) % MOD;
        base_power = base_power * base % MOD;
    }
    return hash_value;
}

long long compute_hash(const string& s, const long long& base) {
    long long hash_value = 0;
    long long base_power = 1;
    for (char c : s) {
        long long value = c -'a' + 1;
        hash_value = (hash_value + value* base_power) % MOD;
        base_power = base_power * base % MOD;
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
 * bfs
 */

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


/**
 * disjoint set union (dsu)
 */

vector<int> parent;
vector<int> length;

void initialize(int n) {
    parent.resize(n + 1);
    length.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        length[i] = 1;
    }
}

int find(int x) {
    while (x != parent[x])
        x = parent[x];
    return x;
}

bool same(int a, int b) {
    return find(a) == find(b);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (length[a] >= length[b]) {
        length[a] += length[b];
        parent[b] = a;
    }
    else {
        length[b] += length[a];
        parent[a] = b;
    }
}

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

/**
 * segment tree
 * 
 * defined as 0-indexed array
 */

vector<int> tree(N);
//int n;

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
 * trie
 * 
 * arrays implementation
 */

class Trie {

    static const int B = 30;
    static const int MAXNODES = 3e5 * 31 + 10;
    
    int nxt[MAXNODES][2];
    int cnt[MAXNODES];
    int node_cnt = 1;

    void initialization() {
        nxt[0][0] = nxt[0][1] = 0;
        cnt[0] = 0;
    }

    int new_node() {
        int index = node_cnt;
        node_cnt++;
        nxt[index][0] = nxt[index][1] = 0;
        cnt[index] = 0;
        return index;
    }

    void insert(int val) {
        int curr = 0;
        for (int b = B; b >= 0; b--) {
            int bit = (val >> b) & 1;
            if (!nxt[curr][bit]) {
                nxt[curr][bit] = new_node();
            }
            curr = nxt[curr][bit];
            cnt[curr]++;
        }
    }

    int search(int val) {
        int curr = 0;
        int res = 0;
        for (int b = B; b >= 0; b--) {
            int bit = (val >> b) & 1;
            if (nxt[curr][bit] != 0 && cnt[nxt[curr][bit]] > 0) {
                curr = nxt[curr][bit];
                res += (bit << b);
            }
            else {
                curr = nxt[curr][bit ^ 1];
                res += ((bit ^ 1) << b);
            }
        }
        return res;
    }

    void remove(int val) {
        int curr = 0;
        cnt[curr]--;    // using one key, so decrement at root
        for (int b = B; b >= 0; b--) {
            int bit = (val >> b) & 1;
            curr = nxt[curr][bit];
            cnt[curr]--;
        }
    }
};

/**
 * find centroids of a tree
 * 
 * 1 or 2 centroids maximum (Jordan theorhem)
 */

vector<int> find_centroids(vector<vector<int>>& adj, int n) {
    vector<int> centroids;
    vector<int> sz(n + 1, 0);
    vector<bool> is_centroid(n + 1, true);
    auto dfs = [&](int node, int parent, auto&& dfs) -> void {
        sz[node] = 1;
        for (auto neigh : adj[node]) {
            if (neigh == parent) continue;
            dfs(neigh, node, dfs);
            sz[node] += sz[neigh];
            if (sz[neigh] > n / 2) {
                is_centroid[node] = false;
            }
        }
        if (n - sz[node] > n / 2) {
            is_centroid[node] = false;
        }
        if (is_centroid[node]) {
            centroids.push_back(node);
        }
    };    

    dfs(1, -1, dfs);
    
    return centroids;
}

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

/**
 * coordinate compression
 * 
 * code by Errichto
 * 
 * complexity: O(n log(n)) due to sorting
 * 
 * example:
 *     vector<int> v = {6, 5, 1};
 *     v = coordinateCompression(v);
 *     // v = {2, 1, 0}
 * 
 */

template <typename T>
vector<T> coordinate_compression(vector<T>& v) {
    int n = v.size();
    vector<pair<T, int>> pairs(n);
    for(int i = 0; i < n; ++i) {
        pairs[i] = {v[i], i};
    }
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && pairs[i - 1].first != pairs[i].first) 
            nxt++;
        v[pairs[i].second] = nxt;
    }
    return v;
}

/**
 * custom hash function to avoid to get hacked
 * 
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
 * compute the binary representation of a number
 * 
 * e.g. binary_representation(6) returns {0, 0, ...0, 1, 1, 0}
 */

int B = 32;

vector<int> binary_representation(long long x) {
    vector<int> res(B);
    for (int i = 0; i < B; i++) {
        int p2 = 1 << i;
        if ((x & p2) > 0) {
            res[B - 1 - i] = 1;
        }
        else {
            res[B - 1 - i] = 0;
        }
    }
    return res;
}

/**
 * compute the number of inversion and sort the vector
 * 
 * on a vector v of size n: auto inversion = inversion_count(v, 0, n - 1)
 */

long long merge(vector<int>& v, int l1, int r1, int l2, int r2) {
    vector<int> sorted;
    int ite1 = l1;
    int ite2 = l2;
    long long count = 0;
    while (ite1 <= r1 && ite2 <= r2) {
        if (v[ite2] < v[ite1]) {
            sorted.push_back(v[ite2]);
            count += r1 - ite1 + 1;
            ite2++;
        }
        else {
            sorted.push_back(v[ite1]);
            ite1++;
        }
    }
    while (ite1 <= r1) {
        sorted.push_back(v[ite1]);
        ite1++;
    }
    while (ite2 <= r2) {
        sorted.push_back(v[ite2]);
        ite2++;
    }
    for (int i = 0; i < r2 - l1 + 1; i++) {
        v[l1 + i] = sorted[i];
    }
    return count;
}

long long inversion_count(vector<int>& v, int l, int r) {
    long long count = 0;
    if (l == r) {
        return 0; // already sort
    }
    int mid = (0ll + r + l) / 2;
    count += inversion_count(v, l, mid);
    count += inversion_count(v, mid + 1, r);
    count += merge(v, l, mid, mid + 1, r);
    return count;
}

/**
 * geometry
 */

 /**
 *  closest pair of points problem using sweep line algorithm
 *  points = {{x1, y1}, 1}, {{x2, y2}, 2}, ...., {{xn, yn, n} 
 *  indices are kept in memory in case output requires indices 
 */

vector<int> find_closest(vector<pair<pair<int, int>, int>>& points, int n) {
    
    auto compute_distance = [&](pair<int, int> p1, pair<int, int> p2) -> long long {
        long long dist = (p1.first - p2.first) * (p1.first - p2.first) \
                       + (p1.second - p2.second) * (p1.second - p2.second);
        return dist;
    };
    
    sort(points.begin(), points.end());

    long long best_dist = INF64;
    int j = 0;
    set<pair<pair<int, int>, int>> neighbours;
    vector<int> closest_points;
    for (int i = 0; i < n; i++) {
        long long d = ceil(sqrt(best_dist));

        while (points[i].first.first - points[j].first.first > d) {
            neighbours.erase({{points[j].first.second, points[j].first.first}, points[j].second});
            j++;
        }

        auto lower = neighbours.lower_bound({{points[i].first.second - d, 0}, -INF32});
        auto upper = neighbours.upper_bound({{points[i].first.second + d, 0}, -INF32});

        for (auto ite = lower; ite != upper; ite++) {
            pair<int, int> other = {ite->first.second, ite->first.first};
            long long dist = compute_distance(points[i].first, other);
            
            if (dist < best_dist) {
                best_dist = dist;
                closest_points = {points[i].second, ite->second};
            }
        }

        neighbours.insert({{points[i].first.second, points[i].first.first}, points[i].second});
    }
    return closest_points;
}

/** compute slope
 * 
 * compute the slope of the vector (p2.first - p1.first, p2.second - p1.second)
 * oriented to the right, e.g. (1, 1) and (-1, -1) are similar
 *  
 */

pair<int, int> compute_slope(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first > p2.first) swap(p1, p2);

    int u = p2.first - p1.first;
    int v = p2.second - p1.second;

    if (u == 0) v = 1;
    if (v == 0) u = 1;
    
    int g = gcd(abs(u), abs(v));
    u /= g; v /= g;
    return {u, v};
}


/**
 *  
 */

 int main() {
    return 0;
}
