/**Kattis - redbluetree
 * If we can find a spanning tree with >= k blue edges and one with <= k blue edges, then we can
 * find a spanning tree with exactly k blue edges (I too wonder what the proof is). We can thus just
 * find the minimum and maximum spanning tree assuming blue edges are weighted 1 and red edges are
 * weighted 0 and check if min_cost <= k <= max_cost.
 *
 * Time: O(E log E), Space: O(E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

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

int n, e, u, v, w;
int k;
vector<tuple<int, int, int>> el;
int main() {
    cin >> n >> e >> k;
    el.clear();
    int min_cost = 0;

    for (int i = 0; i < e; i++) {
        char c;
        cin >> c;
        cin >> u >> v;
        u--, v--;
        el.emplace_back(c == 'B' ? 1 : 0, u, v);
    }
    sort(el.begin(), el.end());

    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        min_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    // cout << min_cost << endl;

    int max_cost = 0;
    sort(el.begin(), el.end(), greater<tuple<int, int, int>>());
    UnionFind uf2(n);
    for (auto &[w, u, v] : el) {
        if (uf2.isSameSet(u, v)) continue;
        max_cost += w;
        uf2.unionSet(u, v);
        if (uf2.numDisjointSets() == 1) break;
    }
    // cout << max_cost << endl;

    if (min_cost <= k && k <= max_cost) {
        cout << "1" << endl;
    } else {
        cout << "0" << endl;
    }
}