/**Kattis - arcticnetwork
 * Observe that this is a variant of the classic MST. We can use Kruskal's algorithm and once we
 * have exactly s connected components left, we can join all of them via the satellite channels,
 * achieving optimality. Also, we report max weight rather than total weight.
 *
 * Time: O(V^2 log V), Space: O(V^2)
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

int t, n, s, u, v, w;
double max_cost;
vector<pair<int, int>> nodes;
vector<tuple<double, int, int>> el, mst_el;

int tc;
int main() {
    cin >> tc;
    while (tc--) {
        cin >> s >> n;
        nodes.assign(n, make_pair(0, 0));
        mst_el.clear();
        el.clear();
        max_cost = 0;
        for (int i = 0; i < n; i++) {
            cin >> nodes[i].first >> nodes[i].second;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                el.push_back(make_tuple(
                    hypot(nodes[i].first - nodes[j].first, nodes[i].second - nodes[j].second), i,
                    j));
            }
        }
        sort(el.begin(), el.end());

        UnionFind uf(n);
        for (auto &[w, u, v] : el) {
            if (uf.isSameSet(u, v)) continue;
            // Edge (u, v) is part of the MST
            mst_el.emplace_back(w, u, v);
            max_cost = w;
            uf.unionSet(u, v);
            if (uf.numDisjointSets() == s) break;
        }

        cout << setprecision(2) << fixed << max_cost << endl;
    }
}