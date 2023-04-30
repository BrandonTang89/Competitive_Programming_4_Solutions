/**Kattis - dragonball1
 * Let S be the set of {cities containing a dragonball} union {0}. We want to do TSP on S starting
 * from 0 and ending anywhere. To do this TSP, we need to Dijkstra from each u in S and update an
 * adjacency matrix. Relatively routine question.
 * 
 * Time: O(E log E + 2^7 * 7^2), Space: O(E + V)
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

int n, e;
int n2;
vector<vector<ll>> adjmat;
vector<vector<tuple<ll, int>>> adjlist;
vector<int> ballcities;

vector<vector<ll>> memo;

ll dp(int u, int bm)
{
    if (bm == 0) return 0;
    if (memo[u][bm] != -1) return memo[u][bm];

    ll ans = 1e18;
    int nbm = bm;
    while (nbm != 0) {
        int v = __builtin_ctz(nbm);
        nbm ^= (1 << v);

        ans = min(ans, adjmat[u][v] + dp(v, bm ^ (1 << v)));
    }
    return memo[u][bm] = ans;
}
int main()
{
    fast_cin();
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<ll, int>>());
    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adjlist[a].push_back({c, b});
        adjlist[b].push_back({c, a});
    }
    n2 = 1;
    map<int, int> ballmap;
    ballmap[0] = 0;
    ballcities.push_back(0);
    for (int i = 0; i < 7; i++) {
        int a;
        cin >> a;
        a--;
        if (ballmap.find(a) == ballmap.end()) {
            ballmap[a] = n2;
            ballcities.push_back(a);
            n2++;
        }
    }
    adjmat.assign(n2, vector<ll>(n2, 1e18));

    for (int i = 0; i < n2; i++) {
        adjmat[i][i] = 0;
        // Dijkstra from i
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        vector<ll> dist(n, 1e18);
        dist[ballcities[i]] = 0;
        pq.push({0, ballcities[i]});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [w, v] : adjlist[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        for (int j = 0; j < n2; j++) {
            adjmat[i][j] = dist[ballcities[j]];
        }
    }

    memo.assign(n2, vector<ll>(1 << n2, -1));
    cout << dp(0, (1 << n2) - 2) << endl;

    return 0;
}