#include <string>
#include <iostream>

uisng namespace std;

/**
 * Polynomial hashing
 * 
 * We use two independent hashes to reduce
 * the probability of collisions
 */

const long long M1 = 1000000007;
const long long M2 = 1000000009;
const long long A1 = 911382323;
const long long A2 = 972663749;

vector<long long> h1, h2, p1, p2;

void preprocessHashing(const string& s) {
    int n = s.size();

    h1.resize(n); h2.resize(n);
    p1.resize(n); p2.resize(n);

    h1[0] = s[0];
    h2[0] = s[0];
    p1[0] = 1;
    p2[0] = 1;

    for (int i = 1; i < n; i++) {
        h1[i] = (h1[i - 1] * A1 + s[i]) % M1;
        p1[i] = (p1[i - 1] * A1) % M1;

        h2[i] = (h2[i - 1] * A2 + s[i]) % M2;
        p2[i] = (p2[i - 1] * A2) % M2;
    }
}

pair<long long, long long> compute(int l, int r) {
    long long hash1 = h1[r];
    long long hash2 = h2[r];

    if (l > 0) {
        hash1 = (hash1 - h1[l - 1] * p1[r - l + 1] % M1 + M1) % M1;
        hash2 = (hash2 - h2[l - 1] * p2[r - l + 1] % M2 + M2) % M2;
    }

    return {hash1, hash2};
}

int main() {
    string s = "ABCABABC";
    preprocessHashing(s);
    pair<long long, long long> hash = compute(2, 5);
    cout << "The hash of CABA is {" << hash.first << ", " << hash.second << "}\n";

    cout << '\n';
}
