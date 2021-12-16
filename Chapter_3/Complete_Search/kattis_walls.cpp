/**Kattis - walls
 * Note that the answer varies from 1 to 4 (or impossible). We just try each answer. Use Github
 * Copilot to improve coding speed since the code is largely repetitive.
 *
 * Time: O(n^4), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;

const ld EPS = 1e-12;
vector<pair<ld, ld>> centers;
vector<vector<int>> cranes;

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}
int main() {
    int l, w, n, r;
    cin >> l >> w >> n >> r;
    ld x, y;
    centers = {{-l / (ld)2, 0}, {l / (ld)2, 0}, {0, -w / (ld)2}, {0, w / (ld)2}};
    cranes.assign(n, vi());

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        for (int j = 0; j < 4; j++) {
            if (dist({x, y}, centers[j]) - r <= EPS) {
                cranes[i].push_back(j);
            }
        }
        // Try using 1 crane
        if (cranes[i].size() == 4) {
            cout << 1 << endl;
            return 0;
        }
    }
    int bm;
    // Try using only 2 cranes
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bm = 0;
            for (auto a : cranes[i]) {
                bm |= 1 << a;
            }
            for (auto a : cranes[j]) {
                bm |= 1 << a;
            }
            if (bm == 15) {
                cout << 2 << endl;
                return 0;
            }
        }
    }

    // Try using 3 cranes
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                bm = 0;
                for (auto a : cranes[i]) {
                    bm |= 1 << a;
                }
                for (auto a : cranes[j]) {
                    bm |= 1 << a;
                }
                for (auto a : cranes[k]) {
                    bm |= 1 << a;
                }
                if (bm == 15) {
                    cout << 3 << endl;
                    return 0;
                }
            }
        }
    }

    // Try using 4 cranes
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    bm = 0;
                    for (auto a : cranes[i]) {
                        bm |= 1 << a;
                    }
                    for (auto a : cranes[j]) {
                        bm |= 1 << a;
                    }
                    for (auto a : cranes[k]) {
                        bm |= 1 << a;
                    }
                    for (auto a : cranes[l]) {
                        bm |= 1 << a;
                    }
                    if (bm == 15) {
                        cout << 4 << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << "Impossible" << endl;

    return 0;
}