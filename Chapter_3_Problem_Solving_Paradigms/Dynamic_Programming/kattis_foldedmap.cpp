/**Kattis - foldedmap
 * We start by padding the map with 0s at the borders such that the map is of the size (2*Th + Ah).
 * (2*Tw + Aw).Then we pre-compute for 2D static RSQ. Then we try all possible offsets of the tiles.
 * Observe that we only need to try starting the tile is the top left Th by Tw squares of the map
 * and we only need to place O(Ah/Th * Aw/Tw) tiles, for each tile, we check if it is needed by
 * seeing if the rsq within that tile is > 0.
 *
 * Time: O(Aw*Ah), Space: O((2*Th + Ah) * (2*Tw + Aw))
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

int Ah, Aw, Th, Tw;
int max_r, max_c;         // width, height;
vector<vector<int>> arr;  // arr[i][j] contains the range sum from (0,0) to (i,j) inclusive

int rsq(int r1, int c1, int r2, int c2) {  // top left, bottom right
    if (r1 < 0 || c1 < 0 || r2 >= max_r - 1 || c2 >= max_c - 1)
        return 0;  // boundary condition check

    if (r1 == 0 && c1 == 0) return arr[r2][c2];
    if (r1 == 0) return arr[r2][c2] - arr[r2][c1 - 1];
    if (c1 == 0) return arr[r2][c2] - arr[r1 - 1][c2];

    return (arr[r2][c2] - arr[r2][c1 - 1] - arr[r1 - 1][c2] + arr[r1 - 1][c1 - 1]);
}

int main() {
    while (cin >> Ah >> Aw >> Th >> Tw) {
        max_r = Ah + 2 * Th;
        max_c = Aw + 2 * Tw;
        arr.assign(max_r, vi(max_c, 0));
        for (int r = Th; r < max_r - Th; r++) {
            for (int c = Tw; c < max_c - Tw; c++) {
                char x;
                cin >> x;
                arr[r][c] = (x == 'X') ? 1 : 0;
            }
        }
        for (int r = 0; r < max_r; r++) {
            for (int c = 0; c < max_c; c++) {
                // 2D Static Prefix Sum Preprocesing
                if (r == 0 && c == 0) continue;
                if (r == 0) {
                    arr[r][c] += arr[r][c - 1];
                } else if (c == 0) {
                    arr[r][c] += arr[r - 1][c];
                } else {
                    arr[r][c] += (arr[r - 1][c] + arr[r][c - 1] - arr[r - 1][c - 1]);
                }
            }
        }
        int ans = 1e9;
        for (int r = 0; r < Th; r++) {
            for (int c = 0; c < Tw; c++) {
                // first box starts at (r, c)
                int cur = 0;
                for (int boxr = r; boxr < max_r; boxr += Th) {
                    for (int boxc = c; boxc < max_c; boxc += Tw) {
                        int r2 = boxr + Th - 1;
                        int c2 = boxc + Tw - 1;
                        cur += min(rsq(boxr, boxc, r2, c2), 1);
                    }
                }
                ans = min(ans, cur);
                // printf("r: %d, c: %d, cur: %d\n", r, c, cur);
            }
        }
        cout << ans << endl;
    }
    return 0;
}