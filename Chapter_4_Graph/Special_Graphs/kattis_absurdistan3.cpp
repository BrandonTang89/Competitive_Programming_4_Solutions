/**Kattis - absurdian3
 * Perfect Bipartite Matching. We let the left vertices be the set of cities and the right vertex be
 * the set of roads (so the degree of each vertex on the right is 2). We then find a perfect
 * matching and output the edges.
 * 
 * Time: O(VE), Space: O(n)
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

int n;
vector<pair<int, int>> edges;
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

int main()
{
    cin >> n;
    adjlist.assign(n * 2, vector<int>());
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.push_back({u, v});
        adjlist[u].push_back(n + i);
        adjlist[v].push_back(n + i);
    }

    // Get a perfect matching
    int MCBM = cal_MCBM(n, n);
    assert(MCBM == n);

    for (int i = 0; i < n; i++) {
        int edgeNum = match[i] - n;
        int u = edges[edgeNum].first;
        int v = edges[edgeNum].second;

        assert(i == u || i == v);
        if (i == u)
            cout << u + 1 << " " << v + 1 << endl;
        else
            cout << v + 1 << " " << u + 1 << endl;
    }

    return 0;
}