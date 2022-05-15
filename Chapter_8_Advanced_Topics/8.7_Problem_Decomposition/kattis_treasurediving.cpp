/**Kattis - treasurediving
 * A combination of SSSP and modified TSP. Notice that we are only concerned with moving between the
 * source, and the idols. So we can start by SSSP with Dijkstra from the source + idols to all other
 * source + idols. Then we can construct the adjacency matrix which we can use for our TSP. During
 * the TSP part, we keep track of where we are (u), the stuff we have yet to visit (mask), and the
 * amount of air we have left (air_left). If we don't have enough air_left to go back, we just die
 * there (-INF). Else we can either just go back, or take another treasure somewhere. Use the memory
 * saving technique of using a map as the memo array since there will be many unvisited states.
 * 
 * Time: O(num_idols * (E log N) + air_left*2^num_idols*num_idols^2)
 * Space: O(air_left*2^num_idols*num_idols)
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
#define LSOne(S) ((S) & -(S))

int n, e, num_idols, INF = 1e9, initial_air;
vector<int> idol_locations;
vector<vector<int>> adjmat;
vector<vector<pair<int, int>>> adjlist;  // w, v
vector<int> dist, sources;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;


map<tuple<int, int, int>, int> memo; //  memo[9][(1 << 8) + 1][1000001];  // u, mask, air_left
int dp(int u, int mask, int air_left) {
    if (air_left < 0) return -INF;
    if (memo.find({u, mask, air_left}) != memo.end()) return memo[{u, mask, air_left}];

    int &ans = memo[{u, mask, air_left}];
    if (air_left < adjmat[u][num_idols]) return ans = -INF; // cant go back

    ans = 0;  // go back to source as a last resort, alr checked that is possible
    int m = mask;
    while (m) {                                                // up to O(n)
        int two_pow_v = LSOne(m);                              // but this is fast
        int v = __builtin_ctz(two_pow_v);
        ans = max(ans,  1 + dp(v, mask ^ two_pow_v, air_left - adjmat[u][v]));  // keep the min
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> n >> e;
        adjlist.assign(n, vector<pair<int, int>>());
        for (int i = 0; i < e; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adjlist[u].emplace_back(w, v);
            adjlist[v].emplace_back(w, u);
        }
        cin >> num_idols;
        idol_locations.resize(num_idols);
        for (int i = 0; i < num_idols; i++) {
            cin >> idol_locations[i];
        }
        sources = idol_locations;
        sources.emplace_back(0);

        adjmat.assign(num_idols + 1, vector<int>(num_idols + 1, INF));

        for (int i = 0; i < (int)sources.size(); i++) {
            int source = sources[i];
            dist.assign(n, INF);
            dist[source] = 0;
            pq.emplace(0, source);
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d > dist[u]) continue;  // inferior pair
                for (auto &[w, v] : adjlist[u]) {
                    if (dist[u] + w >= dist[v])
                        continue;  // relaxing through this node doesn't help
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }

            for (int j = 0; j < (int)sources.size(); j++) {
                int dest = sources[j];
                adjmat[i][j] = dist[dest];
            }
        }
        
        cin >> initial_air;
        memo.clear();
        cout << dp(num_idols, (1 << num_idols) - 1, initial_air) << endl;
    }

    return 0;
}