/**Kattis - airports
 * Minimum Path Cover on DAG. We model a graph G where each node is a flight and there is an edge
 * u->v if we can use the same plane for flight u as for v. Then we are finding the minimum number
 * of paths on G that cover all flights. To do this, we do floyd warshall on the original graph (of
 * the airports) first to find the shortest path between any two airports (inclusive of all the
 * inspection times). Then we add u->v if the u.starting_time + u.flight_time + u.inspection_time +
 * adjmat[u][v] <= v.starting_time.
 *
 * To do the min path cover, we decopose the DAG into a bipartite graph where the left partition is
 * the out nodes and the right partition is the in nodes from G. Then we find the maximum matching
 * in the bipartite graph and report m - matching size (see CP4 for more details).
 *
 * Time: O(n^3 + m^3 (in the worst case)), Mem: O(n^2 + m^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, m;
vector<vector<ll>> adjmat, ori;
vector<ll> inspection_time;

vector<tuple<int, int, ll>> flights;

int bn;
vector<vector<int>> adjlist;  // of the bipartite graph

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
int cal_MCBM()
{
    match.assign(2 * m, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < m; L++) freeV.emplace(L);
    int MCBM = 0;
    int Vleft = m;  // number of vertices in left partition

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

int main()
{
    cin >> n >> m;
    inspection_time.assign(n, 0);
    adjmat.assign(n, vector<ll>(n, 1e9));
    ori.assign(n, vector<ll>(n, 1e9));
    for (int i = 0; i < n; i++) {
        cin >> inspection_time[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adjmat[i][j];
            ori[i][j] = adjmat[i][j];
            adjmat[i][j] += inspection_time[j];
        }
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

    bn = 2 * m;
    adjlist.assign(bn, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        flights.push_back({a, b, c});
    }

    for (int u = 0; u < m; u++) {
        for (int v = 0; v < m; v++) {
            if (u == v) continue;

            auto [a1, b1, t1] = flights[u];
            auto [a2, b2, t2] = flights[v];

            if (t1 + ori[a1][b1] + inspection_time[b1] + adjmat[b1][a2] <= t2) {  // u out to v in
                adjlist[u].push_back(v + m);
            }
        }
    }

    cout << m - cal_MCBM() << endl;
    return 0;
}