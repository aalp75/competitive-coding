#include <iostream>
#include <algorithm>
#include <string>

#include "../../debug.h"

using namespace std;

const long long INF64 = 1e18;

/**
 * Knuth-Morris-Pratt Algorithm
 * 
 * Compute the prefix function pi[i] = ...
 */


vector<int> kmp(const string &s) {
	int n = (int)s.size();
	vector<int> pi(n);
	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && s[j] != s[i]) { 
            j = pi[j - 1]; 
        }
        if (s[i] == s[j]) { 
            j++; 
        }
        pi[i] = j;
	}
	return pi;
}

/**
 * Compute the longest prefix palindrom using the prefix function
 * 
 * 
 */


string longestPrefixPalindrom(string s) {
    string s2 = s;
    reverse(s2.begin(), s2.end());
    s = s + '#' + s2;
    vector<int> pi = kmp(s);

    int length = pi[s.size() - 1];
    string res;
    for (int i = 0; i < length; i++) {
        res += s[i];
    }
    return res;
}

int main() {

    string s = "ABCCBADABC";
    auto pi = kmp(s);

    debug(pi);

    string res = longestPrefixPalindrom(s);
    debug(res);

	return 0;
}