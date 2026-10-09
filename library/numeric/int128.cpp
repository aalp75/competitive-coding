#include <iostream>
#include <algorithm>
#include <string>

#include "../debug.h"

using namespace std;

const long long INF64 = 1e18;

/**
 * To avoid overflow with 64bits integer (long long) it's possible to use 
 * __int128 that is using 128 bits ranging from 
 * -1.7 × 10^38 to 1.7 × 10^38
 * 
 * It's not part of standard C++ but it's a compiler extension available
 * on gcc and clang
 * 
 * By default it's not possible to use cout with __int128 but we can
 * overload the operator <<
 */

using ll128 = __int128;

ostream& operator<<(ostream& os, __int128 x) {
    if (x == 0) {
        return os << '0';
    }

    if (x < 0) {
        os << '-';
        x = -x;
    }

    string s;

    while (x > 0) {
        s += char('0' + x % 10);
        x /= 10;
    }

    reverse(s.begin(), s.end());

    return os << s;
}


int main() {

    ll128 x = (__int128)1000000000000000000LL * 10000000000000000000LL;

    cout << x << '\n';
    x += 1;
    cout << x << '\n';

	return 0;
}