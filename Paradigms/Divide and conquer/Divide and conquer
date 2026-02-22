#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    double x{}, y{}, z{};
    bool operator<(const Point& o) const { return x < o.x; }
};

static inline double Dist(const Point& a, const Point& b) {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    const double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

static double BruteForceMin(const vector<Point>& v) {
    double best = numeric_limits<double>::infinity();
    for (int i = 0; i < (int)v.size(); ++i) {
        for (int j = i + 1; j < (int)v.size(); ++j) {
            best = min(best, Dist(v[i], v[j]));
        }
    }
    return best;
}

static void Solve(const vector<Point>& p, double& best) {
    if ((int)p.size() < 4) {
        best = min(best, BruteForceMin(p));
        return;
    }

    const int mid = (int)p.size() / 2;

    vector<Point> left, right;
    left.assign(p.begin(), p.begin() + mid);
    right.assign(p.begin() + mid, p.end());

    Solve(left, best);
    Solve(right, best);

    vector<Point> strip;
    strip.reserve(p.size());

    if (!left.empty()) {
        const double xL = left.back().x;
        for (int i = (int)left.size() - 1; i >= 0; --i) {
            if (fabs(left[i].x - xL) >= best) break;
            strip.push_back(left[i]);
        }
    }

    if (!right.empty()) {
        const double xR = right.front().x;
        for (int i = 0; i < (int)right.size(); ++i) {
            if (fabs(right[i].x - xR) >= best) break;
            strip.push_back(right[i]);
        }
    }

    best = min(best, BruteForceMin(strip));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> p;
    p.reserve(n);

    for (int i = 0; i < n; ++i) {
        Point t{};
        cin >> t.x >> t.y >> t.z;
        p.push_back(t);
    }

    sort(p.begin(), p.end());

    double ans = numeric_limits<double>::infinity();
    Solve(p, ans);

    cout << ans;
    return 0;
}
