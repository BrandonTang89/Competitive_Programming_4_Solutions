/**Kattis - svemir
 * Mostly a standard MST question. However, considering all n(n-1)/2 edges is MLE and TLE. But,
 * observe that we can treat each pair of nodes (u, v) as having 3 edges, with the weights |x[u] -
 * x[v]|, |y[u] - y[v]| and |z[u] - z[v]|. If we sort the nodes by x coordinates, notice that if u
 * and v are not next to each other in the sorted array, then the edge with weight |x[u] - x[v]| is
 * not useful at all. This is that edge will be heavier than the edges (u, u+1), (u+1, u+2), ... ,
 * (v-1, v) where v < u WLOG, meaning that it will not be chosen as part of the MST. We can do this
 * on the y and z axes to reduce the number of edges to 3(n-1). We can then directly apply kruskal's
 * algorithm and get the answer.
 * 
 * Time: O(n log n), Space: O(n)
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

int n, u, v, w, total_cost;
vector<tuple<int, int, int>> el;
vector<tuple<int, int>> xs, ys, zs;
int main() {
    cin >> n;
    total_cost = 0;

    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        xs.push_back(make_tuple(x, i));
        ys.push_back(make_tuple(y, i));
        zs.push_back(make_tuple(z, i));
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    sort(zs.begin(), zs.end());
    for (int i = 0; i < n - 1; i++) {
        el.emplace_back(get<0>(xs[i + 1]) - get<0>(xs[i]), get<1>(xs[i]), get<1>(xs[i + 1]));
        el.emplace_back(get<0>(ys[i + 1]) - get<0>(ys[i]), get<1>(ys[i]), get<1>(ys[i + 1]));
        el.emplace_back(get<0>(zs[i + 1]) - get<0>(zs[i]), get<1>(zs[i]), get<1>(zs[i + 1]));
    }
    sort(el.begin(), el.end());

    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        total_cost += w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }

    cout << total_cost << endl;
}