/**vjudge - UVA-10181
 * More or less a re-write of the solution from the cp-book repository. Mostly straightforward with the IDA*, but
 * we have a mathematical filter in there which i do not know how to derive and yet is important for the AC.
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

int blank_pos = -1, limit;
int board[16];
vector<int> rec_movs(46);  // recorded moves

inline int heu() {  // sum of all manhattan distances between pieces and their target positions
    int ans = 0;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (r * 4 + c == blank_pos) {
                continue;
            } else {
                ans += abs(board[r * 4 + c] / 4 - r) + abs(board[r * 4 + c] % 4 - c);
            }
        }
    }
    return ans;
}

inline int delta_heu(int r, int c, int nr, int nc) {  // current blank position, new blank position
    int target = board[nr * 4 + nc];
    int tc = target % 4, tr = target / 4;
    return -abs(tr - nr) - abs(tc - nc) + abs(tr - r) +
           abs(tc - c);  // remove old piece, add new piece
}
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char moves[] = "URDL";
int lim;
bool dfs(int u, int g, int h) {  // current blank pos, cost of coming here, heuristic cost
    // cout << u << " " << g << " " << h << endl;
    if (g + h > limit) return false;
    if (h == 0) {
        lim = g;
        return true;
    }

    int r = u / 4, c = u % 4;
    for (int i = 0; i < 4; i++) {
        if (g != 0 && ((rec_movs[g-1] ^ 2) == i)) continue;  // dont go backwards
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
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
    for (limit = h; limit <= 45; limit += 2) {
        if (dfs(blank_pos, 0, h)) return limit;
    }
    return -1;
}

int main() {
    fast_cin();
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        for (int u = 0; u < 16; u++) {
            cin >> board[u];
            if (board[u] == 0) {
                blank_pos = u;
                board[u] = 15;
            } else
                board[u]--;
        }

        // I guess some sort of mathematical thing to filter out impossible cases
        int sum = 0;
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < i; j++)
                if (board[j] > board[i]) sum++;
        sum += blank_pos / 4 + blank_pos % 4;
        //sum -= 15 / 4 + 15 % 4;

        if (sum % 2 != 0 || ida() == -1) {
            cout << "This puzzle is not solvable." << endl;
        } else {
            for (int i = 0; i < lim; i++) {
                cout << moves[rec_movs[i]];
            }
            cout << endl;
        }
    }

    return 0;
}