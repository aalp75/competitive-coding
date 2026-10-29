#include <vector>
#include <iostream>
#include <string>

using namespace std;

/**
 * Z-algorithm
 *
 * Compute the Z-array of a string, the length of the longest
 * prefix match at each position
 * 
 * z[k] = p means that s[0...p-1] = s[k...k + p - 1]
 * 
 * Example: s = "ABCABABC"
 *          z = [00020300]
 * 
 * Note that z[0] is not well defined and is set to 0 but it 
 * can to be changed for some problems (to n for example)
 * 
 * Complexity: O(n)
 */

vector<int> zAlgo(string& s) {
    int n = s.size();
    vector<int> z(n, 0);

    int l = 0;
    int r = 0;

    for (int i = 1; i < n; i++) {
        if (i < r) {
            // we are in Z-box [l, r[ so we know 
            // that z[i] is at least equal to z[i - l]
            z[i] = min(r - i, z[i - l]);
        }

        // can we extend the Z-box [l, r]
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        // update the Z-box
        if (i + z[i] > r) {
            l = i;
            r = z[i] + i;
        }
    }
    return z;
}

int main () {
    string s = "ABCABABC";
    vector<int> z = zAlgo(s);
    cout << "Initial string is " << s << '\n';
    cout << "Z array is: [ ";
    for (auto e : z) {
        cout << e << " ";
    }
    cout << "]\n";
}