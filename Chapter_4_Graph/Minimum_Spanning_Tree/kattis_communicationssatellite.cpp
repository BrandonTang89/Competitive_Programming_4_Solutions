/**Kattis - communicationssatellite
 * Relatively straightforward MST problem. We construct a perfect graph such that the weight of edge
 * (u, v) is dist(center of u, center of v) - radius of u - radius of v. Then we run Kruskal's
 * algorithm to determine the total cost of the MST and report it.
 *
 * Time: O(N^2 log N), Mem: O(N^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

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

int n, e;
vector<tuple<double, int, int>> edges, nodes;
int main() {
    cin >> n;
    e = n * (n - 1) / 2;
    edges.resize(e);

    for (int i = 0; i < n; i++) {
        double r;
        int x, y;
        cin >> x >> y >> r;
        nodes.emplace_back(r, x, y);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double r1, r2, x1, x2, y1, y2;
            tie(r1, x1, y1) = nodes[i];
            tie(r2, x2, y2) = nodes[j];
            double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            edges.emplace_back(dist - r1 - r2, i, j);
        }
    }
    double total_cost = 0;
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    for (auto &[w, u, v] : edges) {
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        total_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    cout << fixed << setprecision(10) << total_cost << endl;

    return 0;
}