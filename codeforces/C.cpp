//#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "../debug.h"
#else
#define debug(...)
#endif

using namespace std;

using ll = long long;

const ll MOD = 998'244'353;
int INF32 = 1e9 + 100;
ll INF64 = 2e18+ 100;

void preprocess() {
}

void solve(int test_case) {
    cerr << "test case #" << test_case << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);
    int t = 1;
    cin >> t;
    preprocess();
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    cerr << "Successful\n";
    return 0;
}

