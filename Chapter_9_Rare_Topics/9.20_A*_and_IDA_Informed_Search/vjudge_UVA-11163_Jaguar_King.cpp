/**vjudge - UVA-11163
 * A modification from the classic 15 pieces sliding puzzle. Here the number of rows is variable
 * and also we can slide left to wrap around to the right and vice versa. As such, we need to
 * modify the heuristic function to account for this, it is a modified manhattan distance where
 * the effect of the columns is either 0, 1 or 2 depending on whether the 2 columns are the
 * same, differ by 1 or 3, differ by 2 (mod 4) respectively. Also we don't need to print
 * the actual answer, but just its size.
 * 
 * Time: O(?), Space: O(num_cells)
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

int blank_pos = -1, limit, final_cost; 
int num_rows, num_cells;
vector<int> board;
vector<int> rec_movs(100);  // recorded moves

inline int heu() {  // sum of all manhattan distances between pieces and their target positions
    int ans = 0;
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < 4; c++) {
            if (r * 4 + c == blank_pos) {  // we dpn't count that as part of the heuristic
                continue;
            } else {
                int tc = board[r * 4 + c] % 4, tr = board[r * 4 + c] / 4;
                ans += abs(tr - r) + (tc != c) + ((tc ^ c) == 2);
            }
        }
    }
    return ans;
}

inline int delta_heu(int r, int c, int nr, int nc) {  // current blank position, new blank position
    int target = board[nr * 4 + nc];
    int tc = target % 4, tr = target / 4;
    return -(abs(tr - nr) + (tc != nc) + ((tc ^ nc) == 2)) +
           (abs(tr - r) + (tc != c) + ((tc ^ c) == 2));  // remove old piece, add new piece
}
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char moves[] = "URDL";

bool dfs(int u, int g, int h) {  // current blank pos, cost of coming here, heuristic cost
    // cout << u << " " << g << " " << h << endl;
    if (g + h > limit) return false;
    if (h == 0) {
        final_cost = g;
        return true;
    }

    int r = u / 4, c = u % 4;
    for (int i = 0; i < 4; i++) {
        if (g != 0 && ((rec_movs[g - 1] ^ 2) == i)) continue;  // dont go backwards
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nr >= num_rows) continue;
        nc = (nc + 4) % 4;
        int nu = nr * 4 + nc;
        int delta = delta_heu(r, c, nr, nc);
        swap(board[u], board[nu]);
        rec_movs[g] = i;
        if (dfs(nu, g + 1, h + delta)) return true;
        swap(board[nu], board[u]);
    }

    return false;
}

int ida() {
    int h = heu();
    for (limit = h; limit <= 100; limit++) {
        if (dfs(blank_pos, 0, h)) return limit;
    }
    return -1;
}

int main() {
    fast_cin();
    for (int set_counter=1;; set_counter++){
        cin >> num_cells;
        if (num_cells == 0)break;
        num_rows = num_cells / 4;
        board.resize(num_cells);

        for (int u = 0; u < num_cells; u++) {
            cin >> board[u];
            if (board[u] == 1) {
                blank_pos = u;
            }
            board[u]--;
        }

        ida();
        cout << "Set " << set_counter << ":\n";
        cout << final_cost << endl;
        /*
        for (int i = 0; i < final_cost; i++) {
            cout << moves[rec_movs[i]];
        }
        cout << endl;*/
    }

    return 0;
}