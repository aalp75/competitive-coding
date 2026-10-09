#include <bits/stdc++.h>

#include "../debug.h"

using namespace std;

using ll = long long;

/**
 * Succesdor graphs (or functional graphs)
 * 
 * The outdegree of each node is 1
 * 
 * We can represent the graph by a vector 'succ' where
 * succ[i] = successor of i
 * 
 * In those graph we can esaily compute the k-th successor 
 * of x in log(k) by precomputing the successor of power of 2
 * 
 */

void querySuccessor(vector<int>& succ, int n) {
    
    const int B = 30; // 60 if k is up to 1e18

    // precompute

    vector<vector<int>> precomp(n, vector<int> (B));

    for (int i = 0; i < n; i++) {
        precomp[i][0] = succ[i];
    }

    for (ll b = 1; b < B; b++) {
        for (int i = 0; i < n; i++) {
            precomp[i][b] = precomp[(precomp[i][b - 1])][b - 1];
        }
    }

    // query - (example: start at node 2 and move forward 76 times)

    int cur = 2;
    int length = 76;

    for (int b = B - 1; b >= 0; b--) {
        if ((1ll << b) & length) {
            cur = precomp[cur][b];
        }
    }

    cout << cur << '\n';
}

/**
 * Cycle detection using Floyd’s algorithm
 * 
 * (also named Tortoise and Hare algorithm)
 * 
 * One possible approach to find all cycles:
 *     - run a dsu to find all components
 *     - run this algorithm on each components
 * 
 */

void findCycle(vector<int>& succ, int start) {

    int a = succ[start];
    int b = succ[succ[start]];
    while (a != b) {
        a = succ[a];    
        b = succ[succ[b]];
    }

    // find the length
    b = succ[a];
    length = 1;
    while (a != b) {
        b = succ[b];
        length++;
    }
}


int main() {
    vector<int> succ = {1, 5, 1, 0, 3, 2};
    querySuccessor(succ, succ.size());

    return 0;
}