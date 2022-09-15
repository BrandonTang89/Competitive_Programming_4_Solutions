/**Kattis - treehouses
 * relatively easy question that is just regular MST but some of the nodes are already connected
 * together with either the open land or existing cables. We generate the edges between nodes that
 * haven't already been connected then run Kruskal's algorithm.
 * 
 * Time: O(n^2), Space: O(n^2)
 */
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

int n, e, u, v, w, p;
double total_cost;
vector<pair<double, double>> nodes;
vector<tuple<double, int, int>> el;
int main() {
    cin >> n >> e >> p;
    UnionFind uf(n);
    for (int i = 1; i < e; i++) {
        uf.unionSet(0, i);
    }
    total_cost = 0;

    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        nodes.emplace_back(x, y);
    }
    for (int i = 0; i < p; i++) {
        cin >> u >> v;
        u--, v--;
        uf.unionSet(u, v);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!uf.isSameSet(i, j)) {
                double dist = sqrt(pow(nodes[i].first - nodes[j].first, 2) +
                                   pow(nodes[i].second - nodes[j].second, 2));
                el.emplace_back(dist, i, j);
            }
        }
    }
    sort(el.begin(), el.end());

    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        total_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    cout << fixed << setprecision(10) << total_cost << endl;
}