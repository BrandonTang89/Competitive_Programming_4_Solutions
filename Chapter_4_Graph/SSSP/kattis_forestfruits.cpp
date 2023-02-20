/**Kattis - forestfruits
 * The Dijkstra stuff is pretty standard. Make sure to read the question carefully, what we need to
 * return is the minimum distance walked PER DAY, not in total to collect all fruits. Also this
 * distance is the distance to the fruit clearing and back, i.e. 2 * distance.
 *
 * Clearly the greedy strategy (pick the closest available clearing each day) is the best since all
 * the clearings regrow at the same rate, picking the closest one first is optimal since it'll
 * regrow first and we can pick it again (if we need to). Formally, suppose we have some candidate
 * sequence of clearings, we can exchange the first clearing we visit (and any subsequent times we
 * visit that) with the nearest clearing for a sequence that is just as good. Repeat this with the
 * second clearing and so on.
 *
 * The difficulty is dealing with edge cases when the clearings don't grow back fast enough or when
 * we don't need to revisit the same clearing. Look at the code for details. Also use long longs.
 *
 * Time: O(E log V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll n, e, c, k, m;
vector<vector<tuple<ll, ll>>> adjlist;
vector<ll> dist;
vector<ll> clearings_with_fruit;
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

int main()
{
    cin >> n >> e >> c >> k >> m;
    adjlist.assign(n, vector<tuple<ll, ll>>());
    dist.assign(n, 1e18);

    for (int i = 0; i < e; i++) {
        ll u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;

        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    clearings_with_fruit.resize(c);
    for (int i = 0; i < c; i++) {
        cin >> clearings_with_fruit[i];
        clearings_with_fruit[i]--;
    }

    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adjlist[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    vector<ll> dist_to_fruit;
    for (int i = 0; i < c; i++) {
        if (dist[clearings_with_fruit[i]] != (ll)1e18)
            dist_to_fruit.push_back(dist[clearings_with_fruit[i]]);
    }
    c = dist_to_fruit.size();
    sort(dist_to_fruit.begin(), dist_to_fruit.end());

    if (k > c && m > c) {
        cout << -1 << endl;
    }

    else if (k > c) {  // m <= c we can't loop back but we can still complete this
        cout << 2LL * dist_to_fruit[m - 1] << endl;
    }
    else {  // k <= c
        cout << 2LL * dist_to_fruit[min(k, m) - 1]
             << endl;  // loop back if needed, else just stop once we have enough fruits
    }
    return 0;
}