/**Kattis - crowdcontrol
 * A medium length problem. First step is MST (maximum), then we DFS from 0 to n-1 to get the path
 * (both vertices and edges). Then we loop through all edges to find the blockable edges (edges that
 * have at least 1 end in the path). Then we see which edges are blockable but not used.
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

int t, n, e, u, v, w;
vector<tuple<int, int, int, int>> el;     // w, u, v, label
vector<vector<tuple<int, int>>> adjlist;  // w, v, label

bool visited[1001];
pair<int, int> parent[1001];
void dfs(int u) {
    visited[u] = true;
    for (auto &[v, label] : adjlist[u]) {
        if (!visited[v]) {
            parent[v] = {u, label};
            dfs(v);
        }
    }
}
int main() {
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<int, int>>());

    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        el.emplace_back(w, u, v, i);
    }
    sort(el.begin(), el.end(), greater<tuple<int, int, int, int>>());

    UnionFind uf(n);
    for (auto &[w, u, v, label] : el) {
        if (uf.isSameSet(u, v)) {
            continue;
        }
        // Edge (u, v) is part of the MST
        adjlist[u].emplace_back(v, label);
        adjlist[v].emplace_back(u, label);
        uf.unionSet(u, v);
    }

    dfs(0);
    int cur = n - 1;
    unordered_set<int> path = {cur};
    set<int> used, blockable;
    while (cur != 0) {
        int u = cur;
        cur = parent[u].first;
        // cout << "passing through " << cur << endl;
        path.insert(cur);
        used.insert(parent[u].second);
    }

    for (auto &[w, u, v, label] : el) {
        if ((int)path.count(u) + (int)path.count(v) >= 1) {
            blockable.insert(label);
        }
    }

    bool none = true;
    for (auto i : blockable) {
        if (!used.count(i)) {
            cout << i << " ";
            none = false;
        }
    }

    if (none) {
        cout << "none";
    }
}