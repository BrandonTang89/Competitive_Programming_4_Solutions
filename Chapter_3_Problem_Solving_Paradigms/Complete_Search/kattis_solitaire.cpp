/**Kattis - solitaire
 * Straightforward recursive backtracking.
 * 
 * Time: O(8^8), Mem: O(8)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h = 5, w = 9;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};
char board[9][9];
int maxDepth;

void rec(int depth)
{
    maxDepth = max(maxDepth, depth);
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (board[r][c] != 'o') continue;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                int nnr = r + 2 * dr[i];
                int nnc = c + 2 * dc[i];

                if (nnr < 0 || nnr >= 9 || nnc < 0 || nnc >= 9) continue;
                if (board[nr][nc] != 'o') continue;
                if (board[nnr][nnc] != '.') continue;

                board[r][c] = '.';
                board[nr][nc] = '.';
                board[nnr][nnc] = 'o';

                rec(depth + 1);

                board[r][c] = 'o';
                board[nr][nc] = 'o';
                board[nnr][nnc] = '.';
            }
        }
    }
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        int pegs = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'o') pegs++;
            }
        }
        maxDepth = 0;
        rec(0);
        cout << pegs - maxDepth << " " << maxDepth << endl;
    }

    return 0;
}