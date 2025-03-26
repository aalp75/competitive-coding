#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "../debug.h"
#else
#define debug(...)
#endif

using namespace std;

typedef long long ll;

ll MOD = 1e9 + 7;
const int N = 2e5 + 10;
int INF32 = 1e15;
ll INF64 = 1e18;

void preprocess() {
}

void solve(int test_case) {
    debug(test_case);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        preprocess();
        solve(i);
    }
    string exit_status = "Successful";
    debug(exit_status);
    return 0;
}

