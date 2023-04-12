/**Kattis - taxicab
 * Minimum Path Cover on a DAG. Quite standard, refer to CP4 book for more info.
 *
 * Time: O(n^3), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<tuple<int, int, int, int, int>> stops;
vector<vector<int>> adjlist;

vector<int> match, visited;
int aug(int L)
{
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}
int cal_MCBM(int Vleft, int Vright)
{
    match.assign(Vleft + Vright, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < Vleft; L++) freeV.emplace(L);
    int MCBM = 0;

    for (int L = 0; L < Vleft; L++) {  // all left vectices
        vector<int> candidates;
        for (auto R : adjlist[L]) {  // all right vectices neighbouring u
            if (match[R] == -1) {    // if v is unassigned
                candidates.push_back(R);
            }
        }
        if ((int)candidates.size() > 0) {
            MCBM++;
            freeV.erase(L);
            int a = rand() % candidates.size();
            match[candidates[a]] = L;
            match[L] = candidates[a];
        }
    }

    // MCBM Calculation
    for (auto &L : freeV) {
        visited.assign(Vleft, 0);
        MCBM += aug(L);
    }

    return MCBM;
}

int inline dist(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        stops.resize(n);
        adjlist.assign(n * 2, vector<int>());

        for (int i = 0; i < n; i++) {
            int hr, mi, x, y, a, b;
            scanf("%d:%d %d %d %d %d", &hr, &mi, &x, &y, &a, &b);
            stops[i] = {hr * 60 + mi, x, y, a, b};
        }
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (u == v) continue;
                auto [t1, x1, y1, a1, b1] = stops[u];
                auto [t2, x2, y2, a2, b2] = stops[v];
                if (t1 > t2) continue;

                if (dist(a1, b1, x2, y2) + dist(x1, y1, a1, b1) + 1 + t1 <= t2) {
                    adjlist[u].push_back(v + n);
                }
            }
        }

        cout << n - cal_MCBM(n, n) << endl;
    }

    return 0;
}