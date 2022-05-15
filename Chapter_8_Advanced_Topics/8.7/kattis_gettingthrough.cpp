/**Kattis - gettingthrough
 * Pretty interesting problem in graph modelling. The key insight is that we can model the
 * sensors as nodes, and 2 nodes are connected if and only if a person of diameter d can pass
 * between them. We can then determine if its impossible for a person of diameter d to pass
 * though by determining if we can find a path from any node that is close enough to the left
 * wall (such that a person of size d cannot go between the left wall and said node) to any
 * node that is close enough to the right wall. Having this "check_connectivity" information,
 * we can then BSTA for the largest diameter (and thus radius) that can pass through.
 * 
 * Time: O(n^2 log 100), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, w;
vector<tuple<int, int, int>> sensors;
vector<vector<ld>> adjmat;

ld largest_passable_diameter(int i, int j) {
    auto &[x1, y1, r1] = sensors[i];
    auto &[x2, y2, r2] = sensors[j];

    ld d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) - r1 - r2;
    if (d < 0) return 0;
    return d;
}

vector<bool> visited;
void dfs(int u, ld size) {
    visited[u] = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && adjmat[u][i] <= size) {
            dfs(i, size);
        }
    }
}
bool check_connectivity(ld size) {
    // determine which sensors intersect with the left wall
    vector<int> left_sensors, right_sensors;

    for (int i = 0; i < n; i++) {
        auto &[x, y, r] = sensors[i];
        if (x - r <= size) left_sensors.push_back(i);
        if (w - (x + r) <= size) right_sensors.push_back(i);
    }
    visited.assign(n, false);
    for (auto i : left_sensors) {
        if (visited[i]) continue;
        dfs(i, size);
    }

    for (auto i : right_sensors) {
        if (visited[i]) return true;
    }
    return false;
}
int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        int x, y, r;
        cin >> w >> n;
        adjmat.assign(n, vector<ld>(n, 0));
        sensors.clear();
        for (int i = 0; i < n; i++) {
            cin >> x >> y >> r;
            sensors.push_back(make_tuple(x, y, r));
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                adjmat[i][j] = adjmat[j][i] = largest_passable_diameter(i, j);
            }
        }

        ld hi = w, lo = 0;
        for (int i = 0; i < 100; i++) {
            ld mid = (hi + lo) / 2;
            if (check_connectivity(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        cout << fixed << setprecision(6) << hi / 2.0 << endl;
    }

    return 0;
}