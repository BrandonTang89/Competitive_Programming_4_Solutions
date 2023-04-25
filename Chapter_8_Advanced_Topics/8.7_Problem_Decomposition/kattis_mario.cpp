/**Kattis - mario
 * Horrendous question. Apparently the solution says that mario arrives within O(n^2 W) time or
 * never. I don't really know how to prove this. What I could do, was to model this as a SSSP
 * problem since reaching a boat at an earlier time is always beneficial and the time to reach a new
 * boat is always non-negative. As such, we use Dijkstra. To find the time needed to wait for a boat
 * v assuming we at boat u at time t, we binary search a list of precomputed meeting times within
 * the lcm of the periods of oscillation of both boats.
 *
 * The biggest issue is you need to realise that mario can jump between boats at t = 0.5 + int. I.e.
 * if 2 boats swap positions, he could have jumped between them. Dealing with this is very annoying.
 * The best solution I could do is just multiply w and all (l, r) by 2. I.e. scale up the entire map
 * by 2. This barely ACs, with almost TLEing (if you use long longs it TLEs). A trick is to remove
 * duplicate boats because they have a lot of meeting times.
 *
 * Time: O(n^2 w^2), Space: O(n^2 w^2)
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

int n, w;
vector<int> dist;
vector<pair<int, int>> boats;
vector<vector<int>> lcmperiod;
vector<vector<vector<int>>> meeting_times;
vector<int> periodu, lenu, confirmed;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int inline pos(int u, int t)
{
    int curu = t % periodu[u];
    if (curu > lenu[u])
        curu = boats[u].first + periodu[u] - curu;
    else
        curu = boats[u].first + curu;
    return curu;
}
int timetowait(int t, int u, int v)
{
    if (meeting_times[u][v].empty()) return -1;
    auto it =
        lower_bound(meeting_times[u][v].begin(), meeting_times[u][v].end(), t % lcmperiod[u][v]);
    if (it == meeting_times[u][v].end())
        return lcmperiod[u][v] - (t % lcmperiod[u][v]) + meeting_times[u][v][0];
    return *it - (t % lcmperiod[u][v]);
}
int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> w;
        w *= 2;
        set<pair<int, int>> s;
        boats.clear();
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            l *= 2;
            r *= 2;
            if (s.find({l, r}) != s.end()) continue;
            s.insert({l, r});
            boats.push_back({l, r});
        }
        n = boats.size();
        boats.push_back({0, 0});
        boats.push_back({w, w});

        lenu.resize(n + 2);
        periodu.resize(n + 2);
        for (int i = 0; i < n + 2; i++) {
            lenu[i] = boats[i].second - boats[i].first;
            periodu[i] = max(lenu[i] * 2, 1);
        }
        meeting_times.assign(n + 2, vector<vector<int>>(n + 2, vector<int>()));
        lcmperiod.assign(n + 2, vector<int>(n + 2, 1));
        for (int i = 0; i < n + 2; i++) {
            for (int j = i + 1; j < n + 2; j++) {
                lcmperiod[i][j] = lcmperiod[j][i] = lcm(periodu[i], periodu[j]);

                for (int t = 0; t < lcmperiod[i][j]; t++) {
                    if (pos(i, t) == pos(j, t)) {
                        meeting_times[i][j].push_back(t);
                        meeting_times[j][i].push_back(t);
                    }
                }
            }
        }

        confirmed.assign(n + 2, 0);
        dist.assign(n + 2, 1e8);
        dist[n] = 0;

        while (!pq.empty()) pq.pop();
        pq.push({0, n});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            if (u == n + 1) break;
            confirmed[u] = 1;
            for (int v = 0; v < n + 2; v++) {
                if (confirmed[v]) continue;

                int t = timetowait(d, u, v);
                if (t == -1) continue;
                assert(t >= 0);
                if (dist[v] > d + t) {
                    dist[v] = d + t;
                    pq.push({d + t, v});
                }
            }
        }

        if (dist[n + 1] == 1e8)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << dist[n + 1] / 2 << endl;
    }

    return 0;
}