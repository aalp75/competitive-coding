#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MOD = 1e9 + 7;
const int N = 1e3;
int MAX_INT = 1e9;

/**
 * modular expression
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

ll div(const ll& x, const ll& y) { // x / y
    return mul(x, inverse(y));
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

