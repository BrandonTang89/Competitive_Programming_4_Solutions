/**Kattis - spider
 * If we let edge L be the special edge within our web, we can use Kruskal's algorithm to determine
 * the variant MST value in O(E log E) by first joining the nodes connected by L then greedily
 * selecting the minimum edge that does not create a cycle. But observe that doing this will take
 * only a subset of the true MST edges, specifically it will take all the MST edges except the
 * heaviest one on the path between u and v on the initial MST where edge L joins u and v. Let the
 * heaviest edge on the path between u and v on the true MST be maxweight[u][v], if we can
 * precompute these values, we will be able to determine the cost of the varinat MST, taking a
 * specific edge L as the special edge in O(1). This allows us to check all edges in O(E) time. But
 * how can we precompute maxweight[u][v]? Well, we can start by creating the true MST in O(E log E),
 * then we can just DFS from each node to all other nodes to find maxweight[u][v]. in O(V^2). And we
 * are done...
 *
 * Time: O(E log E + V^2), Space: O(E + V^2)
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

ll n, e, u, v, w, total_cost;
vector<tuple<ll, ll, ll>> el;
vector<vector<tuple<ll, ll>>> adjlist;
vector<vector<ll>> maxweight;
ll ans = 0;

vector<int> visited;
void dfs(int source, int u) {
    visited[u] = 1;
    for (auto &[v, w] : adjlist[u]) {
        if (visited[v] == 0) {
            maxweight[source][v] = max(maxweight[source][u], w);
            dfs(source, v);
        }
    }
}
int main() {
    fast_cin();
    while (cin >> n >> e) {
        el.clear();
        adjlist.assign(n, vector<tuple<ll, ll>>());
        maxweight.assign(n, vector<ll>(n, -1));
        total_cost = 0;

        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            u--, v--;
            el.emplace_back(w, u, v);
        }
        sort(el.begin(), el.end());

        UnionFind uf(n);
        for (auto &[w, u, v] : el) {
            if (uf.isSameSet(u, v)) {
                continue;
            }
            adjlist[u].emplace_back(v, w);
            adjlist[v].emplace_back(u, w);
            total_cost += w;
            uf.unionSet(u, v);
        }

        if (uf.numDisjointSets() != 1) {
            cout << "disconnected" << endl;
            continue;
        }
        ans = total_cost;

        for (int i = 0; i < n; i++) {
            visited.assign(n, 0);
            maxweight[i][i] = 0;
            dfs(i, i);
        }

        for (auto &[w, u, v] : el) {
            ans = min(ans, total_cost - maxweight[u][v] - w);
        }
        cout << ans << endl;
    }
}