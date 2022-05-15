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

int n;
vector<tuple<int, int, int>> gears;
vector<vector<int>> adjlist;

ld euc_dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void reduceFraction(int &x, int &y) {
    int d;
    d = __gcd(x, y);
    x /= d;
    y /= d;
}

vector<int> dist;  // 0 is unvisited, 1 is turning clockwise, 2 is turning counterclockwise
queue<int> q;
int main() {
    cin >> n;
    gears.resize(n);
    adjlist.assign(n, vector<int>());

    for (int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        gears[i] = {x, y, r};
    }

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            auto &[x1, y1, r1] = gears[u];
            auto &[x2, y2, r2] = gears[v];

            if (abs(euc_dist(x1, y1, x2, y2) - (r1 + r2)) <= 1e-9) {
                adjlist[u].push_back(v);
                adjlist[v].push_back(u);
            }
        }
    }

    dist.assign(n, 0);
    q.push(0);
    dist[0] = 1;
    bool locking = false;
    while (!q.empty() && !locking) {
        int u = q.front();
        q.pop();
        for (int v : adjlist[u]) {
            if (dist[v] == 0) {
                dist[v] = (dist[u] == 1 ? 2 : 1);
                q.push(v);
            } else if (dist[v] == dist[u]) {
                locking = true;
                break;
            }
        }
    }

    if (locking) {
        cout << -1 << endl;
    } else if (dist[n - 1] == 0) {
        cout << 0 << endl;
    } else {
        int a = get<2>(gears[n - 1]);
        int b = get<2>(gears[0]);

        reduceFraction(a, b);
        b = (dist[0] == dist[n - 1] ? 1 : -1) * b;
        cout << a << " " << b << endl;
    }
    return 0;
}