#include <vector>
#include <queue>

const int INF32 = 1e9 + 10;
const long long INF64 = 1e18 + 10;

using namespace std;

/**
 * coordinate compression
 * 
 * code by Errichto
 * 
 * complexity: O(n log(n)) due to sorting
 * 
 * example:
 *     vector<int> v = {6, 5, 1};
 *     v = coordinateCompression(v);
 *     // v = {2, 1, 0}
 * 
 */

template <typename T>
vector<T> coordinate_compression(vector<T>& v) {
    int n = v.size();
    vector<pair<T, int>> pairs(n);
    for(int i = 0; i < n; ++i) {
        pairs[i] = {v[i], i};
    }
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && pairs[i - 1].first != pairs[i].first) 
            nxt++;
        v[pairs[i].second] = nxt;
    }
    return v;
}