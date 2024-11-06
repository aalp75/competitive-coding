#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MOD = 1e9 + 7;
const int N = 1e3;
int MAX_INT = 1e9;

/**
 * modular operation
 */

ll add(const ll& x, const ll& y) { // x + y
    return (x + y) % MOD; 
}

ll substract(const ll& x, const ll& y) { // x - y
    return(x - y + MOD) % MOD;
}

ll mul(const ll& x, const ll& y) { // x * y
    return (x * y) % MOD; 
}

ll inverse(const ll& x) { // 1 / x
    return x <= 1 ? x : MOD - (ll)(MOD / x) * inverse(MOD % x) % MOD; 
}

ll division(const ll& x, const ll& y) { // x / y
    return mul(x, inverse(y));
}

ll fast_exponentiation(const ll& x, const ll& y) { // x ^ y
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

ll gcd(const ll& x, const ll& y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

ll lcm(const ll& x, const ll& y) {
    return x / gcd(x, y) * y;
}

/**
 * polynomial hashing
 * 
 * MOD = 1e9 + 9 is recommended
 * base = 2 for binary string
 * base = 31 for low characters string
 */

ll compute_hash(vector<int>& s, const ll& base) {
    ll hash_value = 0;
    ll base_power = 1;
    for (auto value : s) {
        hash_value = add(hash_value, mul(value, base_power));
        base_power = mul(base_power, base);
    }
    return hash_value;
}

ll compute_hash(const string& s, const ll& base) {
    ll hash_value = 0;
    ll base_power = 1;
    for (auto c : s) {
        ll value = c -'a' + 1;
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
