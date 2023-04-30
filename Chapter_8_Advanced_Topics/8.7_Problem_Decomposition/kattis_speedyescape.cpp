/**Kattis - speedyescape
 * Got baited by the "dp with preprocessing tag" and wasted alot of time. We do preprocess the times
 * that the police get to each node with a simple Floyd Warshall. But the main section is just a
 * BSTA + Dijkstra to check if we can exit at a certain speed.
 *
 * Time: O(V^3 + 500 * E log E), Space: O(V^2 + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e, h, po, br;
vector<vector<int>> adjmat;
vector<vector<tuple<int, int>>> adjlist;
unordered_set<int> highwayset;
vector<double> policeHereTime;

int main()
{
    fast_cin();
    cin >> n >> e >> h;
    adjmat.assign(n, vector<int>(n, 1e8));
    adjlist.assign(n, vector<tuple<int, int>>());
    for (int i = 0; i < e; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        a--;
        b--;
        adjmat[a][b] = l;
        adjmat[b][a] = l;
        adjlist[a].push_back({l, b});
        adjlist[b].push_back({l, a});
    }

    for (int i = 0; i < n; i++) {
        adjmat[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
            }
        }
    }

    for (int i = 0; i < h; i++) {
        int a;
        cin >> a;
        a--;
        highwayset.insert(a);
    }
    cin >> br >> po;
    br--;
    po--;
    policeHereTime.assign(n, 1e9);
    for (int i = 0; i < n; i++) {
        policeHereTime[i] = (double)adjmat[po][i] / 160.0;
    }

    if (highwayset.find(br) != highwayset.end()) {  // edge case
        cout << "0";
        return 0;
    }

    vector<double> min_time;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    double r =
        20000 * 160;  // brothers cross the whole map before the police move to any adjacent node
    double l =
        (double)160 /
        (double)20000;  // police cross the whole map before the brothers move to any adjacent node
    for (int x = 0; x < 500; x++) {
        double m = (r + l) / 2;

        min_time.assign(n, 1e18);
        pq.push({0, br});
        min_time[br] = 0;

        bool possible = false;
        while (!pq.empty()) {
            auto [t, u] = pq.top();
            pq.pop();
            if (t > min_time[u]) continue;

            if (highwayset.find(u) != highwayset.end()) {
                possible = true;
                break;
            }

            for (auto [w, v] : adjlist[u]) {
                double newtime = t + w / m;
                if (newtime >= min_time[v]) continue;
                if (newtime > policeHereTime[v]) continue;
                min_time[v] = newtime;
                pq.push({newtime, v});
            }
        }
        while (!pq.empty()) pq.pop();

        if (possible) {
            r = m;  // can go slower
        }
        else {
            l = m;
        }
    }

    if (r == 20000 * 160) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << fixed << setprecision(10) << r << endl;
    }

    return 0;
}