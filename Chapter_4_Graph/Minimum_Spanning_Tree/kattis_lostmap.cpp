/**Kattis - lostmap
 * Actually just MST on an adjacency matrix.
 *
 * Observation 1:
 *  Assume we have a partially constructed tree. We can ignore the edges that are between nodes
 *  that are already connected indirectly within the partially constructed tree to maintaio the
 *  tree property.
 *
 *  Consider the minimum weight edge (w, u, v) between 2 nodes that are not directly or indirectly
 *  connected. Realise that this edge has to be added to the tree. If we do not add the edge,
 *  traverse from u to v, we required travelling through at least 2 other edges with weights greater
 *  than w, which means that the distance from u to v will be greater than w which is a contradiction.
 * 
 *  Notice that kruskal's algorithm does exactly this: gets the minimum weight edge between 2 nodes
 *  from different components and adds it to the tree. Thus we are actually generating the minimum
 *  spanning tree.
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
int t, n, e, u, v, w, total_cost;
vector<tuple<int, int, int>> el, mst_el;
int main() {
    fast_cin();
    cin >> n;
    total_cost = 0;

    for (u = 0; u < n; u++) {
        for (v = 0; v < n; v++) {
            cin >> w;
            if (u < v) {
                el.push_back(make_tuple(w, u, v));
            }
        }
    }
    sort(el.begin(), el.end());

    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        mst_el.emplace_back(w, u, v);
        total_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    for (auto &[w, u, v] : mst_el) {
        cout << u + 1 << " " << v + 1 << endl;
    }
}