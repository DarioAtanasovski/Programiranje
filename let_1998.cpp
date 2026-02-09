#include <bits/stdc++.h>
using namespace std;

struct Point3D {
    double x, y, z;
    int id;
};

static inline double dist2(const Point3D& a, const Point3D& b) {
    double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

struct Answer {
    double best2;
    pair<int,int> pairId;
};

static Answer bruteForce(vector<Point3D>& pts, int l, int r) {
    Answer ans{numeric_limits<double>::infinity(), {-1,-1}};
    for (int i = l; i < r; i++) {
        for (int j = i + 1; j < r; j++) {
            double d2 = dist2(pts[i], pts[j]);
            if (d2 < ans.best2) {
                ans.best2 = d2;
                ans.pairId = {pts[i].id, pts[j].id};
            }
        }
    }
    return ans;
}

static Answer solveDC(vector<Point3D>& pts, int l, int r) {
    int n = r - l;
    if (n <= 32) {
        return bruteForce(pts, l, r);
    }

    int mid = l + n / 2;
    double midX = pts[mid].x;

    Answer leftAns  = solveDC(pts, l, mid);
    Answer rightAns = solveDC(pts, mid, r);

    Answer ans = (leftAns.best2 < rightAns.best2) ? leftAns : rightAns;
    double best = sqrt(ans.best2);

    vector<Point3D> strip;
    strip.reserve(n);
    for (int i = l; i < r; i++) {
        if (fabs(pts[i].x - midX) < best) strip.push_back(pts[i]);
    }

    sort(strip.begin(), strip.end(), [](const Point3D& a, const Point3D& b) {
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });

    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i + 1; j < (int)strip.size(); j++) {
            double dy = strip[j].y - strip[i].y;
            if (dy >= best) break;

            double dz = fabs(strip[j].z - strip[i].z);
            if (dz >= best) continue;


            double d2 = dist2(strip[i], strip[j]);
            if (d2 < ans.best2) {
                ans.best2 = d2;
                ans.pairId = {strip[i].id, strip[j].id};
                best = sqrt(ans.best2);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point3D> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
        pts[i].id = i;
    }

    sort(pts.begin(), pts.end(), [](const Point3D& a, const Point3D& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });

    Answer ans = solveDC(pts, 0, n);

    cout << fixed << setprecision(10);
    cout << "Min distance = " << sqrt(ans.best2) << "\n";
    cout << "Pair ids = " << ans.pairId.first << " " << ans.pairId.second << "\n";
    return 0;
}
