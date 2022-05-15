/**Kattis - pandachess
 * My first "long" problem in a while. Theres 3 parts:
 * 1. Get the correct ordering. 
 *      This is found using topological sort...
 * 2. Reduce LCS problem to LIS problem
 *      Notice that the answer is 2*(n-LCS) since for all non LCS ics, we need to remove the old one
 *      and replace it with the correct one. Since all the pieces are unique we can reduce to the
 *      problem to LIS by replacing the ICS by their index of the topological ordering and then
 *      finding the LIS.
 * 3. Perform n log k LIS which is classic.
 * 
 * Note that this question requires a map instead of vector for anything indexed by the IC.
 * Time: O(n log k), Space: O(n + m)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, d;
map<ll, unordered_set<ll>> adjlist;
map<ll, int> dist;
vector<ll> ts;
unordered_set<ll> ics;
void toposort(ll u) {
    dist[u] = 1;
    for (auto v : adjlist[u]) {
        if (dist[v] == 0) toposort(v);
    }
    ts.emplace_back(u);
}

int main() {
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 0; i < m; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        adjlist[a].insert(b);
        ics.insert(a);
        ics.insert(b);
    }
    for (auto u : ics) {
        if (dist[u] == 0) toposort(u);
    }
    reverse(ts.begin(), ts.end());

    // Now TS is our topological sort, we need to find LCS between it and the current list
    for (int i = 0; i < n; i++) {
        dist[ts[i]] = i+1;  // dist[IC] is the rank
    }

    // Do LIS
    vector<int> v;
    vector<int> L(n, 0);  // L[i] is the minimum last element of an IS of length i
    for (int i = 0; i < n; i++) {
        ll a;
        scanf("%lld", &a);
        if (dist[a] == 0) continue;
        v.push_back(dist[a]);
    }

    int k = 0;  // length of current LIS
    for (int i = 0; i < (int) v.size(); i++) {
        int pos = lower_bound(L.begin(), L.begin() + k, v[i]) - L.begin();
        L[pos] = v[i];
        if (pos == k) {
            k++;
        }
    }
    cout << 2*(n - k) << endl;

    return 0;
}