#include <utility>
#include <numeric>
#include <stdlib.h>

using namespace std;

/** compute slope
 * 
 * compute the slope of the vector (p2.first - p1.first, p2.second - p1.second)
 * oriented to the right, e.g. (1, 1) and (-1, -1) are similar
 *  
 */

pair<int, int> compute_slope(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first > p2.first) swap(p1, p2);

    int u = p2.first - p1.first;
    int v = p2.second - p1.second;

    if (u == 0) v = 1;
    if (v == 0) u = 1;
    
    int g = gcd(abs(u), abs(v));
    u /= g; v /= g;
    return {u, v};
}