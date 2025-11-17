#include <bits/stdc++.h>

using namespace std;

/**
 * Custom implementation of std::lower_bound and std::upper_bound
 * 
 * lower_bound(x): returns the index of first element >= x
 * upper_bound(x): returns the index of first element > x
 * 
 * Note: Use left + (right - left) / 2 instead of (l + r) / 2 
 *       to avoid overflow when working with very large indices
 */

int lower_bound(const vector<int>& v, int x) {
    int n = v.size();

    int left = 0;
    int right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (v[mid] < x) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}

int upper_bound(const vector<int>& v, int x) {
    int n = v.size();

    int left = 0;
    int right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (v[mid] <= x) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}

int main() {
    vector<int> v = {1, 3, 3, 5, 7};

    cout << lower_bound(v, 3) << '\n';
    cout << lower_bound(v, 4) << '\n';
    cout << lower_bound(v, 8) << '\n';

    cout << upper_bound(v, 3) << '\n';
    cout << upper_bound(v, 4) << '\n';
    cout << upper_bound(v, 8) << '\n';

}