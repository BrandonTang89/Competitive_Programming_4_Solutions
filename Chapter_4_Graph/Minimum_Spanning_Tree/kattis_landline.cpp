/**Kattis - landline
 * There are 2 cases. First is if all the nodes are insecure. In this case, all we need to check is
 * if the the graph is presented is complete and report the total sum of weights. Otherwise, what we
 * do is a modified Kruskal's algo where the insecure nodes are only allowed to be leaf vertices in
 * the MST. This is done by ensuring no 2 insecure vertices are joined and that each insecure vertex
 * has degree 1.
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

int p;
int n, e, u, v, w, total_cost;
vector<tuple<int, int, int>> el, mst_el;
unordered_set<int> insecure;
int main() {
    cin >> n >> e >> p;
    total_cost = 0;

    for (int i = 0; i < p; i++) {
        int x;
        cin >> x;
        x--;
        insecure.insert(x);
    }
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        u--, v--;
        el.emplace_back(w, u, v);
    }

    if (p == n) {  // all vertices insecure
        if (e != (n) * (n - 1) / 2) {
            cout << "impossible" << endl;
            return 0;
        }
        for (auto &[w, u, v] : el) {
            total_cost += w;
        }
        cout << total_cost << endl;
        return 0;
    }

    sort(el.begin(), el.end());

    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (insecure.count(u) && insecure.count(v)) continue;
        if (insecure.count(u) && uf.sizeOfSet(u) > 1) continue;
        if (insecure.count(v) && uf.sizeOfSet(v) > 1) continue;
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        mst_el.emplace_back(w, u, v);
        total_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    if (uf.numDisjointSets() != 1) {
        cout << "impossible" << endl;
    } else {
        cout << total_cost << endl;
    }
}