/**Kattis - chesstournament
 * DFS + UFDS. We union all the nodes that are equal then set the "greater than" as edges between
 * (the representatives of) the disjoint sets, we are looking for cycles using DFS.
 * Time: O(V + E), Space: O(V + E)
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
    UnionFind(int N)
    {
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

    void unionSet(int i, int j)
    {
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
vector<pair<int, int>> bigger;
vector<int> visited;
unordered_set<int> groups;

vector<vector<int>> adjlist;
bool cycle;
void dfs(int u)
{
    for (auto v : adjlist[u]) {
        if (visited[v] == 1) {
            cycle = true;
            return;
        }
        if (visited[v] == 0) {
            visited[v] = 1;
            dfs(v);
        }
    }
    visited[u] = 2;
}
int main()
{
    cin >> n >> e;
    UnionFind uf(n);
    for (int i = 0; i < e; i++) {
        int u, v;
        char c;
        cin >> u >> c >> v;
        if (c == '=') {
            uf.unionSet(u, v);
        }
        else
            bigger.push_back({u, v});
    }
    for (int i = 0; i < n; i++) {
        groups.insert(uf.findSet(i));
    }

    adjlist.assign(n, vector<int>());
    for (auto &[u, v] : bigger) {
        u = uf.findSet(u);
        v = uf.findSet(v);
        adjlist[u].push_back(v);
    }
    visited.assign(n, 0);

    for (auto u : groups) {
        if (visited[u] == 0) {
            dfs(u);
        }
    }
    cout << (cycle ? "inconsistent" : "consistent") << endl;

    return 0;
}