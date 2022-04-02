/**Kattis - arrivinontime
 * Dijkstra + BSTA Question. We BSTA for latest start time possible. Verify with Dijkstra
 * on graph with dynamic weights.
 * 
 * Time: O(log(s) * E log V), Space: O(E + V)
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

int n, e, s;
ll INF = 1e12;
vector<tuple<int, ll, ll, ll>> adjlist[100001];  // (v, t0, p, dt)
priority_queue<tuple<ll, int>, vector<tuple<ll, int>>, greater<tuple<ll, int>>> pq;
vector<ll> dist;
bool arrive_on_time(ll start_time) {
    dist.assign(n, INF);
    while (!pq.empty()) pq.pop();
    dist[0] = start_time;
    pq.push(make_tuple(start_time, 0));

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (u == n - 1) break;
        if (d > dist[u]) continue;  // inferior pair

        for (auto &[v, t0, p, dt] : adjlist[u]) {
            ll w;
            if (d <= t0)
                w = t0 - d + dt;  // wait for first train + time to travel
            else {
                w = (p - (d - t0) % p) % p + dt;  // wait for the next train + time to travel
            }
            if (dist[u] + w >= dist[v]) continue;  // relaxing through this node doesn't help
            dist[v] = dist[u] + w;
            pq.emplace(dist[v], v);
        }
    }

    // cout << "possible to leave at " << source_dist << "? " << (dist[n-1] <= s) << endl;
    return (dist[n - 1] <= s);
}
int main() {
    cin >> n >> e >> s;
    for (int i = 0; i < e; i++) {
        int u, v;
        ll t0, p, d;
        cin >> u >> v >> t0 >> p >> d;
        adjlist[u].push_back(make_tuple(v, t0, p, d));
    }
    ll lo = 0, hi = s, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        // cout << "mid " << mid << endl;
        if (arrive_on_time(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    if (arrive_on_time(hi)) {
        lo = hi;
    }

    if (arrive_on_time(lo)) {
        cout << lo << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}