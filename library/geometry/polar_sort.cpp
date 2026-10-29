#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

/**
 * Sort a vector of points by their angle
 * 
 * The cross product can be used to compare 2 points : A(x1, y1) and B(x2, y2).
 * 
 * cross(A, B) = x1 * y2 - y1 * x2
 * 
 * If the cross product is positive, it means that B is on the left of A
 * 
 * For polar sort, first we split in [0, 180[ and [180, 360[
 * and then we find which one is first using cross product.
 * 
 * If A is before B then cross(A, B) > 0
 */

struct Point {
    long long x;
    long long y;

    Point() : x(0), y(0) {}
    Point(long long _x, long long _y) : x(_x), y(_y) {}
};

long long cross(Point p1, Point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

bool up(Point p1) {
    return p1.y > 0 || (p1.y == 0 && p1.x >= 0);
}

bool polarSort(Point p1, Point p2) {
    if (up(p1) == up(p2)) {
        return cross(p1, p2) > 0;
    }
    return up(p1) > up(p2); // upper-half comes first
}


int main() {
    Point C(0, -1);
    Point B(-1, 1);
    Point A(1, 1);

    vector<Point> pts = {C, B, A};

    sort(pts.begin(), pts.end(), polarSort); // A B C

    for (auto pt : pts) {
        cout << pt.x << " " << pt.y << '\n';
    }
}