#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

double X, Y;
int n;
vector<tuple<int, int, double>> shields;  // bottom, top, factor

double f(double horizontalSpeed) {
    // returns the x coordinate of the point when the y coordinate is Y
    double x = 0;
    double y = 0;

    for (auto [shield_bottom, shield_top, factor] : shields) {
        // go to the shield
        double dist_to_shield = shield_bottom - y;
        double time_to_shield = dist_to_shield;
        x += time_to_shield * horizontalSpeed;

        // go through the shield
        double dist_through_shield = shield_top - shield_bottom;
        double time_through_shield = dist_through_shield;
        x += time_through_shield * factor * horizontalSpeed;

        y = shield_top;
    }

    // go to the end
    double dist_to_end = Y - y;
    double time_to_end = dist_to_end;
    x += time_to_end * horizontalSpeed;

    return x;
}

int main() {
    fast_cin();
    bool negate = false;
    cin >> X >> Y;
    if (X < 0) {
        negate = true;
        X = -X;
    }
    cin >> n;
    shields.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        double f;
        cin >> x >> y >> f;
        shields[i] = make_tuple(x, y, f);
    }

    double l = 0;
    double r = 1e9;
    for (int i = 0; i < 500; i++) {
        double m = (l + r) / 2;
        if (f(m) < X) {  // too slow
            l = m;
        } else {
            r = m;
        }
    }

    cout << setprecision(10);
    if (negate) {
        cout << -l << endl;
    } else {
        cout << l << endl;
    }

    return 0;
}