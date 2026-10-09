#include <vector>

using namespace std;

/**
 * compute the binary representation of a number
 * 
 * e.g. binary_representation(6) returns {0, 0, ...0, 1, 1, 0}
 */

int B = 32;

vector<int> binary_representation(long long x) {
    vector<int> res(B);
    for (int i = 0; i < B; i++) {
        int p2 = 1 << i;
        if ((x & p2) > 0) {
            res[B - 1 - i] = 1;
        }
        else {
            res[B - 1 - i] = 0;
        }
    }
    return res;
}
