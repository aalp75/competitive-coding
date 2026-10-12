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

vector<int> zAlgo(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - x], y - i + 1));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            x = i; 
            y = i + z[i];
            z[i]++;
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