#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;
const int N = 1e3;
const long long INF32 = 1e9;
const long long INF64 = 1e18;
int n;

/**
 * modular operation
 */

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
 * bfs
 */

vector<int> bfs(vector<vector<int>>& adj, int n, int node) {
    vector<int> dist(n + 1, INF32);
    queue<int> nodes;
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

vector<int> linker(N);
vector<int> length(N);

void initialize() {
    for (int i = 1; i <= n; i++) {
        linker[i] = i;
        length[i] = 1;
    }
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
    if (a == b) return;
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
    vector<long long> distance(n + 1, INF32);

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
 *  on a vector v of size n: auto inversion = inversion_count(v, 0, n - 1)
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
 *  
 */

int main() {
    return 0;
}
