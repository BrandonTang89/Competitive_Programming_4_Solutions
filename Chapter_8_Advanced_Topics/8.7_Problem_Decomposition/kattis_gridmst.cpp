/**Kattis - gridmst
 * The key insight to this problem is that many of the possible (n)(n-1)/2 edges are actually
 * useless. How do we know which are useful though? Well we do a multi-source BFS from each of the
 * points, whenever the BFS from one point u will overlap with the BFS from another point v, we
 * consider the edge between the u to v to be useful. Why are other edges useless? If the BFS from 2
 * points a and b don't overlap, then there must be some set of points in between a and b such that
 * we would rather use edges between a and that set, as well as b and that set, rather than going
 * from a to b directly. Using 2 edges from a to the set and to b will be <= cost of a to b directly
 * and will include 1 additional node, thus being better for the MST construction, so the direct
 * a to b will be useless... Also after we do this, just simply use kruskal. Oh, also account to remove
 * duplicate points.
 * 
 * Time: O(not easy to analyse), Space: O(depends on num of useful edges)
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

int n;
set<pair<int, int>> points;
pair<int, int> dist[1001][1001];  // dist, parent
set<tuple<int, int, int>> el;     // w, u, v

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
queue<pair<int, int>> q;
int main() {
    cin >> n;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            dist[x][y] = {-1, -1};
        }
    }
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        if (points.count({x, y})) {
            continue;
        }
        points.insert({x, y});
        q.push({x, y});
        dist[x][y] = {0, points.size() - 1};
    }
    n = points.size();
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dr[i];
            int ny = y + dc[i];
            if (nx < 0 || nx >= 1000 || ny < 0 || ny >= 1000) continue;
            if (dist[nx][ny].first != -1) {
                el.emplace(dist[nx][ny].first + dist[x][y].first + 1, // avoid duplicate edges (w, u, v) and (w, v, u)
                           min(dist[nx][ny].second, dist[x][y].second),
                           max(dist[nx][ny].second, dist[x][y].second));
                continue;
            }
            dist[nx][ny] = {dist[x][y].first + 1, dist[x][y].second};
            q.push({nx, ny});
        }
    }
    ll total_cost = 0;
    UnionFind uf(n);
    for (auto &[w, u, v] : el) {
        if (uf.isSameSet(u, v)) continue;
        // Edge (u, v) is part of the MST
        total_cost += (ll)w;
        uf.unionSet(u, v);
        if (uf.numDisjointSets() == 1) break;
    }
    cout << total_cost << endl;
    return 0;
}