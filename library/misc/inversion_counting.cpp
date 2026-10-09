#include <vector>

using namespace std;

/**
 * compute the number of inversion and sort the vector
 * 
 * on a vector v of size n: long long inversion = inversion_count(v, 0, n - 1)
 */

long long merge(vector<int>& v, int l1, int r1, int l2, int r2) {
    vector<int> sorted;
    int ite1 = l1;
    int ite2 = l2;
    long long count = 0;
    while (ite1 <= r1 && ite2 <= r2) {
        if (v[ite2] < v[ite1]) {
            sorted.push_back(v[ite2]);
            count += r1 - ite1 + 1;
            ite2++;
        }
        else {
            sorted.push_back(v[ite1]);
            ite1++;
        }
    }
    while (ite1 <= r1) {
        sorted.push_back(v[ite1]);
        ite1++;
    }
    while (ite2 <= r2) {
        sorted.push_back(v[ite2]);
        ite2++;
    }
    for (int i = 0; i < r2 - l1 + 1; i++) {
        v[l1 + i] = sorted[i];
    }
    return count;
}

long long inversion_count(vector<int>& v, int l, int r) {
    long long count = 0;
    if (l == r) {
        return 0; // already sort
    }
    int mid = (0ll + r + l) / 2;
    count += inversion_count(v, l, mid);
    count += inversion_count(v, mid + 1, r);
    count += merge(v, l, mid, mid + 1, r);
    return count;
}