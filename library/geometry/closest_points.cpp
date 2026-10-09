#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF32 = 1e9 + 10;
const long long INF64 = 1e18 + 10;

/**
 *  closest pair of points problem using sweep line algorithm
 *  points = {{x1, y1}, 1}, {{x2, y2}, 2}, ...., {{xn, yn, n} 
 *  indices are kept in memory in case output requires indices 
 */

vector<int> find_closest(vector<pair<pair<int, int>, int>>& points, int n) {
    
    auto compute_distance = [&](pair<int, int> p1, pair<int, int> p2) -> long long {
        long long dist = (p1.first - p2.first) * (p1.first - p2.first) \
                       + (p1.second - p2.second) * (p1.second - p2.second);
        return dist;
    };
    
    sort(points.begin(), points.end());

    long long best_dist = INF64;
    int j = 0;
    set<pair<pair<int, int>, int>> neighbours;
    vector<int> closest_points;
    for (int i = 0; i < n; i++) {
        long long d = ceil(sqrt(best_dist));

        while (points[i].first.first - points[j].first.first > d) {
            neighbours.erase({{points[j].first.second, points[j].first.first}, points[j].second});
            j++;
        }

        auto lower = neighbours.lower_bound({{points[i].first.second - d, 0}, -INF32});
        auto upper = neighbours.upper_bound({{points[i].first.second + d, 0}, -INF32});

        for (auto ite = lower; ite != upper; ite++) {
            pair<int, int> other = {ite->first.second, ite->first.first};
            long long dist = compute_distance(points[i].first, other);
            
            if (dist < best_dist) {
                best_dist = dist;
                closest_points = {points[i].second, ite->second};
            }
        }

        neighbours.insert({{points[i].first.second, points[i].first.first}, points[i].second});
    }
    return closest_points;
}
