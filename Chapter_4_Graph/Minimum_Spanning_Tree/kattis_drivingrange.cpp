/**Kattis - drivingrange
 * Literally standard MST problem. Track max weight edge instead of total cost, report if
 * impossible.
 *
 * Time: O(E log E), Space: O(E + V)
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

class UnionFind {  // OOP style
   private:
    vi p, rank, setSize;  // vi p is the key part
    int numSets;

   public:
    UnionFind(int N) {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);     // optional speedup
        setSize.assign(N, 1);  // optional feature
        numSets = N;           // optional feature
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    int numDisjointSets() { return numSets; }             // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; }  // optional

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;         // i and j are in same set
        int x = findSet(i), y = findSet(j);  // find both rep items
        if (rank[x] > rank[y]) swap(x, y);   // keep x 'shorter' than y
        p[x] = y;                            // set x under y
        if (rank[x] == rank[y]) ++rank[y];   // optional speedup
        setSize[y] += setSize[x];            // combine set sizes at y
        --numSets;                           // a union reduces numSets
    }
};

int t, n, e, u, v, w, max_cost;
vector<tuple<int, int, int>> el, mst_el;
int main() {
    cin >> n >> e;
    el.clear();
    mst_el.clear();
    max_cost = 0;

    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        el.emplace_back(w, u, v);
    }
    sort(el.begin(), el.end());

    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        mst_el.emplace_back(w, u, v);
        max_cost = max(max_cost, w);
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    if (uf.numDisjointSets() == 1)
        cout << max_cost << endl;
    else
        cout << "IMPOSSIBLE\n";
}