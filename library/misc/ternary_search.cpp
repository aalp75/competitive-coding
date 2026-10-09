#include <iostream>
#include <algorithm>

#include "../debug.h"

using namespace std;

const long long INF64 = 1e18;

/**
 * Ternary search implementation
 * 
 * Find the maximum of a function that is strictly increasing then 
 * stricly decreasing
 * 
 * There is one version for integer and one version for float
 * 
 * To return the minimum just change the comparison 
 * f(m1) < f(m2) to f(m1) > f(m2)
 * 
 */

template <typename F>
long long ternarySearchInteger(long long start, long long end, F f) {
    long long left = start;
    long long right = end;

    while(right  - left > 4) {
        long long mid1 = (left + right) / 2;
        long long mid2 = (left + right) / 2 + 1;

        if (f(mid1) < f(mid2)) {
            left = mid1;
        }
        else {
            right = mid2;
        }
    }

    long long res = -INF64;

    for (long long i = left; i <= right; i++) {
        res = max(res, f(i));
    }
    return res;
}

template <typename F>
long double ternarySearchFloat(long double start, long double end, F f) {
    long double left = start;
    long double right = end;

    long double EPS = 1e-9;

    while(right - left > EPS) {
        long double mid1 = left + (right - left) / 3;
        long double mid2 = right - (right - left) / 3;

        if (f(mid1) < f(mid2)) {
            left = mid1;
        }
        else {
            right = mid2;
        }
    }

    long double res = f(left);
    return res;
}


int main() {

    auto f1 = [&] (long long x) {
        return -(x - 7) * (x - 7) + 100;
    };

    long long res = ternarySearchInteger(0, 20, f1);
    cout << "res: " << res << " (integer)\n";

    auto f2 = [&] (long double x) {
        return -(x - 7.4) * (x - 7.4) + 100;
    };

    double res2 = ternarySearchFloat(0, 20, f2);
    cout << "res : " << res << " (floating)\n";

	return 0;
}