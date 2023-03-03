/**Kattis - borg
 * BFS Floodfill + Minimum Spanning Tree. Clearly we are trying to find the cost of the minimum
 * spanning tree that includes the start and all the aliens. To construct this graph to do MST, we BFS
 * from each alien/source to all other aliens/sources. 
 * 
 * Time: O(NHW + N^2 log N) where N is the number of aliens/sources, Mem: O(HW + N^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int h, w;
vector<string> grid;
vector<tuple<int, int>> idx_to_coord;  // index of aliens/source to coordinate
vector<tuple<int, int, int>> edges;
vector<vector<int>> dist;
queue<tuple<int, int>> q;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

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
int main()
{
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> w >> h;
        idx_to_coord.clear();
        edges.clear();

        grid.assign(h, string());
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < h; i++) {
            getline(cin, grid[i]);
        }

        int n = 0;
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (grid[r][c] == 'A' || grid[r][c] == 'S') {
                    n++;
                    idx_to_coord.push_back(make_tuple(r, c));
                }
            }
        }
        for (int i = 0; i < n; i++) {
            // BFS from idx_to_coord[i]
            dist.assign(h, vector<int>(w, -1));
            auto [r, c] = idx_to_coord[i];
            dist[r][c] = 0;
            q.push(make_tuple(r, c));
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                    if (grid[nr][nc] == '#') continue;
                    if (dist[nr][nc] != -1) continue;
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push(make_tuple(nr, nc));
                }
            }
            for (int j = i + 1; j < n; j++) {
                auto [r, c] = idx_to_coord[j];
                assert(dist[r][c] != -1);
                edges.push_back(make_tuple(dist[r][c], i, j));
            }
        }
        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        int ans = 0;
        for (auto [d, u, v] : edges) {
            if (!uf.isSameSet(u, v)) {
                uf.unionSet(u, v);
                ans += d;
            }
            if (uf.numDisjointSets() == 1) break;
        }
        cout << ans << endl;
    }

    return 0;
}