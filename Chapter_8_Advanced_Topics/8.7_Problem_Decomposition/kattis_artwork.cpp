/**Kattis - artwork
 * Quite an interesting problem? We work backwards, we draw all the strokes first, do 1x counting
 * CCs with floodfill. Then we union the UFDS sets of all cells within the same component.
 * Black cells are still on their own (1 element set). For each stroke in reverse, we undraw the
 * stroke, if any of the cells of the stroke are white after removing the stroke, then we
 * union the 4 adjacent cells to the stroke (if they are white).
 * 
 * Time: O(HW + Q*(max(H,W)))
 * Space: O(HW + Q)
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

int w, h, q;
vector<vector<int>> board, visited;
vector<tuple<int, int, int, int>> strokes;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int cti(int r, int c) { return r * w + c; }
void dfs(int r, int c, int main_vertex, UnionFind &uf) {
    visited[r][c] = 1;
    uf.unionSet(main_vertex, cti(r, c));
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (visited[nr][nc] == 0 && board[nr][nc] == 0) dfs(nr, nc, main_vertex, uf);
    }
}

void merge(int r, int c, UnionFind &uf) {
    int main_vertex = cti(r, c);
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (board[nr][nc] == 0) uf.unionSet(main_vertex, cti(nr, nc));
    }
}
int main() {
    cin >> w >> h >> q;
    board.assign(h, vector<int>(w, 0));
    visited.assign(h, vector<int>(w, 0));
    UnionFind uf(w * h);
    int r1, c1, r2, c2;
    for (int i = 0; i < q; i++) {
        cin >> c1 >> r1 >> c2 >> r2;
        c1--;
        r1--;
        c2--;
        r2--;
        strokes.push_back(make_tuple(r1, c1, r2, c2));

        if (r1 == r2) {
            for (int j = c1; j <= c2; j++) {
                board[r1][j]++;
            }
        } else if (c1 == c2) {
            for (int j = r1; j <= r2; j++) {
                board[j][c1]++;
            }
        }
    }
    int num_black_squares = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] > 0) {
                num_black_squares++;
            } else {
                dfs(i, j, cti(i, j), uf);
            }
        }
    }
    vector<int> ans = {uf.numDisjointSets() - num_black_squares};
    for (int i = q - 1; i > 0; i--) {
        // undo the stroke
        auto &[r1, c1, r2, c2] = strokes[i];
        if (r1 == r2) {
            for (int j = c1; j <= c2; j++) {
                board[r1][j]--;
                if (board[r1][j] == 0) {
                    merge(r1, j, uf);
                    num_black_squares--;
                }
            }
        } else if (c1 == c2) {
            for (int j = r1; j <= r2; j++) {
                board[j][c1]--;
                if (board[j][c1] == 0) {
                    merge(j, c1, uf);
                    num_black_squares--;
                }
            }
        }
        ans.emplace_back(uf.numDisjointSets() - num_black_squares);
    }
    reverse(ans.begin(), ans.end());
    for (auto &x : ans) {
        cout << x << endl;
    }

    return 0;
}