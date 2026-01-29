#include <bits/stdc++.h>

using namespace std;

/**
 * Geometry library
 * 
 * Point2d, Line are based on https://victorlecomte.com/cp-geo.pdf
 * 
 */

/**
 * grid rotation (90 degree counter clockwise) 
 * 
 * grid is represented as a vector<string> n * m
 * 
 */

 void grid_rotation(vector<string>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<string> grid_rotated(grid);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid_rotated[i][j] = grid[j][n - 1 - i];
        }
    }
    grid = grid_rotated;
}

/**
 * Point 2d class
 * 
 * Point is represented as 2 coordinates: x and y.
 * 
 * "type2 of coordinates can be integer (long long) or float (long double) depending
 * on the problem. Most of the time it's better to use type as long but some 
 * operations are only possible using double (e.g rotation, and distance
 * point-segment etc).
 * 
 */

using type = long double; // can be long long or (long) double
struct Point {
    type x, y;
    static constexpr double EPS = 1e-9;

    Point() : x(0), y(0) {}
    Point(type x, type y) : x(x), y(y) {}

    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator*(const Point& p) const { return {x * p.x, y * p.y}; }
    Point operator*(const type a) const { return {a * x, a * y}; }
    
    // only for floating-point
    Point operator/(const Point& p) const { return {x / p.x, y / p.y}; }
    Point operator/(const type n) const { return {x / n, y / n}; }


    // operator== needs to be epsilon-adjusted for floating-point
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    //bool operator==(const Point& p) const { return fabsl(x - p.x) < EPS && fabsl(y - p.y) < EPS; }
    bool operator!=(const Point& p) const { return !(*this == p); }

    long double norm() {
        return sqrtl(x * x + y * y);
    }

    friend ostream& operator<<(ostream& os, Point p) {
        return os << "(" << p.x << p.y << ")";
    }
};

Point translate(Point p, Point v) {
    return p + v;
}

// scale p around center c by a factor 
Point scale(Point c, double factor, Point p) {
    return c + (p - c) * factor;
}

type cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

type dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

Point rotation(Point p, double a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

// 90 degree rotation around center, works with integer
Point perpendicular(Point p) {
    return {-p.y, p.x};
}

double orientation(Point a, Point b, Point c) {
    return cross(b - a, c - a); 
}

bool isPerpendicular(Point v, Point w) {
    return dot(v, w) == 0;
}

long double angle(Point v, Point w) {
    long double cosTheta = dot(v, w) / v.norm() / w.norm();
    return acos(min(max(cosTheta, -1.0l), 1.0l));
}

/**
 * Polar sort
 * 
 * sort points by their argument from 0 to 2 PI
 * 
 * Usage:
 *  vector<Point> v;
 *  sort(v.begin(), v.end(), ref, polarSort)
 *  lower_bound(v.begin(), v.end(), ref, polarSort)
 *  upper_bound(v.begin(), v.end(), ref, polarSort)
 * 
 * half: helper function to check if we are in the upper half or lower half
 * 
 * in order to sort from theta to theta + 2 PI update the half function
 * in order to sort around a given point update the polarSort function
 * 
 */

bool half(Point p) {
    assert (p.x != 0 || p.y != 0) // undefined behavior for (0, 0)
    return p.y > 0 || (p.y == 0 && p.x > 0);
}

// check if p1 and p2 are in the same half and 
// if p2 is on the right of p2 (i.e cross(p1, p2) > 0)
bool polarSort(const Point& p1, const Point& p2) {
    if (half(p1) && !half(p2)) return true;
    if (half(p2) && !half(p1)) return false;
    return cross(p1, p2) > 0;
}

string to_string(Point p) { // used with debug.h
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

/**
 * Line class
 * 
 * Line is represented as a direction v and a positino c
 * such that all points on the line are of the form c + x * v with x in R
 * 
 * it's equivalent to the representation ax + by = c
 * with v = (b, -a) and c = c
 * 
 * (a, b) is the vector normal to the line (i.e (a, b) · (x ,y) = c)
 * 
 */

struct Line {
    Point v; // direction
    type c; // position

    Line() : v(Point()), c(0) {}
    Line(Point v, type c) : v(v), c(c) {}
    Line(Point p, Point q) : v(q - p), c(cross(v, p)) {}
    Line(type a, type b, type c) : v(b, -a), c(c) {} // ax + by = c

    type side(Point p) {
        return cross(v, p) - c;
    }

    double distance(Point p) { // distance between the line and a point
        return abs(side(p) / v.norm());
    }

    // return a line perpendicular to the current line passing by p
    Line perpThrough(Point p) {
        return {p, p + perpendicular(v)};
    }

    // compare projection of p and q along the vector v
    // return true if p appears strictly before q
    // [----Proj(p)----Proj(q)---->
    bool cmpProj(Point p, Point q) { 
        return dot(v, p) < dot(v, q);
    }

    Line translate(Point t) {
        return {v, c + cross(v, t)};
    }

    Line shiftLeft(double dist) {
        return {v, c + dist * v.norm()};
    }

    Point projection(Point p) {
        return p - perpendicular(v) * side(p) / (v.norm() * v.norm());
    }

    Point reflection(Point p) {
        return p - perpendicular(v) * 2 * side(p) / (v.norm() * v.norm());
    }
};

bool intersection(Line l1, Line l2, Point& out) {
    type d = cross(l1.v, l2.v);
    if (d != 0) {
        out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point
        return true;
    }
    else {
        return false;
    }
}

// interior = true means that the bisector direction points in the same direction than l1 and l2
// interior = false means that the bisector direction points in oposite direction of l1
Line bisector(Line l1, Line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // assert that l1 and l2 are not parallel
    double sign = interior ? 1 : -1;
    Point v(l1.v / l1.v.norm() + l2.v / l2.v.norm() * sign);
    type c = l1.c / l1.v.norm() + l2.c / l2.v.norm() * sign;
    return Line(v, c);
}

bool inDisk(Point a, Point b, Point p) {
    return dot(a - p, b - p) <= 0;
}

bool onSegment(Point a, Point b, Point p) { // segment [a, b]
    return orientation(a, b, p) == 0 && inDisk(a, b, p);
}

long double distanceRayPoint(Point a, Point b, Point p) { // ray [a, b)
    if (a != b) {
        Line l(a, b);
        if (l.cmpProj(a, p))
            return l.distance(p);
    }
    return min((p - a).norm(), (p - b).norm());
}

// [a, b] and [c, d] intersection in each other at the point out
// if and only:
// - a and b are on side different of [c, d]
// - c and d are on side different of [a, b]
bool properInter(Point a, Point b, Point c, Point d, Point& out) {
    double oa = orientation(c, d, a);
    double ob = orientation(c, d, b);
    double oc = orientation(a, b, c);
    double od = orientation(a, b, d);

    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

long double distanceSegPoint(Point a, Point b, Point p) {
    if (a != b) {
        Line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b))
            return l.distance(p);
    }
    return min((p - a).norm(), (p - b).norm());
}

long double distanceSegSeg(Point a, Point b, Point c, Point d) {
    Point dummy;
    if (properInter(a, b, c, d, dummy)) return 0; // intersection
    return min({distanceSegPoint(a, b, c), distanceSegPoint(a, b, d),
                distanceSegPoint(c, d, a), distanceSegPoint(c, d, b)});
}

/**
 * Polygon
 * 
 */

long double areaPolygon(vector<Point>& p) {
    int n = p.size();
    long double area = 0.0;
    for (int i = 0; i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]);
    }
    return abs(area) / 2.0;
}

bool isConvex(vector<Point>& p) {
    bool hasPos = false;
    bool hasNeg = false;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int o = orientation(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

bool above(Point a, Point p) { // is Point b higher than Point a
    return p.y >= a.y;
}

bool crossesRay(Point a, Point p, Point q) {
    return (above(a, q) - above(a, p)) * orientation(a, p, q) > 0;
}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<Point>& p, Point a, bool strict = true) {
    int numCrossings = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1;
}

int main() {


}