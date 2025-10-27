#include <bits/stdc++.h>
using namespace std;

struct point {
    long long x, y;
};
typedef long long ll;

bool areCollinear(point p, point q, point r) {
    ll val = (ll)(q.x - p.x) * (r.y - p.y) - 
                     (ll)(q.y - p.y) * (r.x - p.x);
    return val == 0;
}

bool check(point p1, point p2, const vector<point>& all_points) {
    vector<point> remaining_points;
    for (const auto& p : all_points) {
        if (!areCollinear(p1, p2, p)) {
            remaining_points.push_back(p);
        }
    }
    if (remaining_points.size() <= 2) {
        return true;
    }
    for (size_t i = 2; i < remaining_points.size(); i++) {
        if (!areCollinear(remaining_points[0], remaining_points[1], remaining_points[i])) {
            return false; 
        }
    }
    return true; 
}

int main() {
    int n;
    cin >> n;
    if (n <= 4) {
        cout << "YES" << endl;
        return 0;
    }
    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    if (check(points[0], points[1], points)) {
        cout << "YES" << endl;
        return 0;
    }
    if (check(points[0], points[2], points)) {
        cout << "YES" << endl;
        return 0;
    }
    if (check(points[1], points[2], points)) {
        cout << "YES" << endl;
        return 0;
    }
    cout << "NO" << endl;
}