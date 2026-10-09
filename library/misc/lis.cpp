#include <vector>

using namespace std;

/**
 * longest strictly increasing subsequence
 * 
 * replace with upper_bound for increasing or equal
 */

template<typename T>
int LIS(vector<T>& v) {
    vector<T> lis;
    for (auto e : v) {
        auto ite = lower_bound(lis.begin(), lis.end(), e);
        if (ite == lis.end()) lis.push_back(e);
        else *ite = e;
    }
    return lis.size();
}
