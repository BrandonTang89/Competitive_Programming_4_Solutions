/**Kattis - inventing
 * An interesting problem. We process the MST edge list in increasing weight. We observe that if the
 * current edge is (w, u, v) then we can join the components of u and v together. Since this edge is
 * the unique best edge to join these 2 components together, we can assign all the other edges
 * between these 2 components to be of weight (w+1). Then u and v are now in the same component and
 * we can repeat this until we have only 1 component left.
 * 
 * Time: O(n log n), Space: O(n)
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

ll n, e, u, v, w, total_cost;
vector<tuple<ll, ll, ll>> el;
int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> n;
        e = n - 1;
        el.clear();
        total_cost = 0;
        UnionFind uf(n);

        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            el.push_back(make_tuple(w, u - 1, v - 1));
        }
        sort(el.begin(), el.end());
        for (int i = 0; i < e; i++) {
            auto &[w, u, v] = el[i];
            total_cost += w;
            total_cost += (w + 1) * (ll)(uf.sizeOfSet(u) * uf.sizeOfSet(v) - 1);
            uf.unionSet(u, v);
        }

        cout << total_cost << endl;
    }
}