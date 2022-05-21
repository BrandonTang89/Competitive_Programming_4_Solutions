/**vjudge - HDU-1043 (Same as UVA-652)
 * An easier version of UVA-10181. Generally same concepts apply, do IDA*. 
 *
 * Time: O(?), Space: O(1)
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

const int max_moves = 32;  // http://oeis.org/A087725
int blank_pos = -1, limit;
int board[9];
vector<int> rec_movs(max_moves + 2);  // recorded moves

inline int heu() {  // sum of all manhattan distances between pieces and their target positions
    int ans = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (r * 3 + c == blank_pos) {
                continue;
            } else {
                ans += abs(board[r * 3 + c] / 3 - r) + abs(board[r * 3 + c] % 3 - c);
            }
        }
    }
    return ans;
}

inline int delta_heu(int r, int c, int nr, int nc) {  // current blank position, new blank position
    int target = board[nr * 3 + nc];
    int tc = target % 3, tr = target / 3;
    return -abs(tr - nr) - abs(tc - nc) + abs(tr - r) +
           abs(tc - c);  // remove old piece, add new piece
}
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char moves[] = "urdl";
int lim;
bool dfs(int u, int g, int h) {  // current blank pos, cost of coming here, heuristic cost
    // cout << u << " " << g << " " << h << endl;
    if (g + h > limit) return false;
    if (h == 0) {
        lim = g;
        return true;
    }

    int r = u / 3, c = u % 3;
    for (int i = 0; i < 4; i++) {
        if (g != 0 && ((rec_movs[g - 1] ^ 2) == i)) continue;  // dont go backwards
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
        int nu = nr * 3 + nc;
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
    for (limit = h; limit <= 32; limit += 2) {
        if (dfs(blank_pos, 0, h)) return limit;
    }
    return -1;
}

int main() {
    fast_cin();
    char p;
    while (cin >> p) {
        for (int u = 0; u < 9; u++) {
            if (u != 0) cin >> p;
            if (p == 'x') {
                blank_pos = u;
                board[u] = 8;
            } else {
                board[u] = p - '0';
                board[u]--;
            }
        }

        int sum = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < i; j++)
                if (board[j] > board[i]) sum++;
        sum += blank_pos / 3 + blank_pos % 3;
        sum -= 8 / 3 + 8 % 3;
        if (sum % 2 != 0 || ida() == -1) {
            cout << "unsolvable" << endl;
        } else {
            for (int i = 0; i < lim; i++) {
                cout << moves[rec_movs[i]];
            }
            cout << endl;
        }
    }

    return 0;
}