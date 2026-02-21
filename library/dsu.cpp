#include <bits/stdc++.h>

using namespace std;

/**
 * Disjoint Set Union
 * 
 * find, same and unite run in O(log n) time in the worst case
 * 
 * union by size ensures that the height of each tree is at most O(log n),
 * because we always attach the smaller component to the largest one
 */

struct DSU {

    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
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

    // merge smaller component into larger component
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b); // ensure a is the largest component

        parent[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    DSU dsu(3);
    dsu.unite(0, 1);
    
    cout << dsu.same(0, 1) << '\n'; // true
    cout << dsu.same(1, 2) << '\n'; // false
}