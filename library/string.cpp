#include <bits/stdc++.h>

using namespace std;

/**
 * Manacher algorithm - longest palindrome substring in O(n)
 *
 * The function finds longest odd-length palindromes of a given string
 *
 * radius[i] = radius R such that s[i - (R - 1) ... i + (R - 1)] is the
 *             longest palindrome centered at i
 *
 * Example: "ABAYABAX"
 *   index:   0 1 2 3 4 5 6 7
 *   string:  A B A Y A B A X
 *   radius:  1 2 1 4 1 2 1 1
 *   radius[1] = 2  (palindrome "ABA", indices [0...2])
 *   radius[3] = 4  (palindrome "ABAYABA", indices [0...6])
 *
 * To handle even-length palindromes from the original string, 
 * first apply a transformation "ABAC" to "#A#B#A#C#",
 * then all palindromes become odd-length in the transformed string
 * 
 * Key idea:
 *   If [L..R] is a known palindrome centered at C, then for any i < R;
 *   the palindrome at i must be at equivalent to his mirror from the center
 *   i.e radius[i] >= min(radius[2 * C - i], R - i)
 *   Only extensions beyond R require new comparisons
 *
 * Complexity:
 *   The right boundary only moves forward, so total expansions = O(n)
 */

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^"; // used to handle borders
    
    vector<int> radius(n + 2, 0);

    int center = 0;
    int right_boundary = 0;

    for (int i = 1; i <= n; i++) {
        if (i >= right_boundary) { // run normal algorithms
            center = i;
            while (s[i - radius[i]] == s[i + radius[i]]) {
                radius[i]++;
            }
            right_boundary = i + radius[i];
            continue;
        }

        // start from mirror position
        radius[i] = min(radius[2 * center - i], right_boundary - i);
    
        // extend as much as possible
        while (s[i - radius[i]] == s[i + radius[i]]) {
            radius[i]++;
        }

        // check if new right boundary
        if (i + radius[i] > right_boundary) {
            center = i;
            right_boundary = i + radius[i];
        }
    }

    return vector<int>(radius.begin() + 1, radius.end() - 1);
}

string manacher(string s) {
    // transform the initial string
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    t += '#';
    vector<int> radius = manacher_odd(t);

    // generate the longest substring palindrome
    int best_center = 0;
    int best_radius = 0;

    for (int i = 0; i < t.size(); i++) {
        if (radius[i] > best_radius) {
            best_radius = radius[i];
            best_center = i;
        }
    }

    int left = best_center - best_radius + 1;
    int right = best_center + best_radius - 1;

    string palindrome;

    for (int i = left; i <= right; i++) {
        if (t[i] == '#') continue;
        palindrome += t[i];
    }

    return palindrome;
}

int main() {
    string s = "ABAYABAX";
    string palindrome = manacher(s);
    cout << "Initial string is: " << s << '\n';
    cout << "Longest substring palindrome is: " << palindrome << '\n';

    cout << '\n';

    s = "AABBGDAADGBXF";
    palindrome = manacher(s);
    cout << "Initial string is: " << s << '\n';
    cout << "Longest substring palindrome is: " << palindrome << '\n';

    return 0;
}