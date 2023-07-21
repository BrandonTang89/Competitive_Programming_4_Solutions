/**Kattis - minibattleship
 * Relatively easy backtracking question. For each ship, try placing it starting from any square
 * either horizontally or vertically. Note to prevent double counting on ships of length 1 ssince
 * the orientation of the ship doesn't matter in the count).
 * 
 * Time: O(n^2 Choose k), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, k;
vector<int> ships;
vector<string> grid;
vector<string> state;

ll ans;
int valid()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'O' && state[i][j] != '1') return 0;
        }
    }
    return 1;
}
void backtrack(int cur)
{  // trying to put ships[cur]
    if (cur == k) {
        ans += valid();
        return;
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            // try horizontally
            if (c + ships[cur] <= n) {
                bool canPut = true;
                for (int i = 0; i < ships[cur] && canPut; i++) {
                    if (grid[r][c + i] == 'X' || state[r][c + i] == '1') {
                        canPut = false;
                    }
                }

                if (canPut) {
                    for (int i = 0; i < ships[cur]; i++) {
                        state[r][c + i] = '1';
                    }
                    backtrack(cur + 1);
                    for (int i = 0; i < ships[cur]; i++) {
                        state[r][c + i] = '0';
                    }
                }
            }

            // Try vertically
            if (ships[cur] > 1 && r + ships[cur] <= n) {  // prevent double counting
                bool canPut = true;
                for (int i = 0; i < ships[cur] && canPut; i++) {
                    if (grid[r + i][c] == 'X' || state[r + i][c] == '1') {
                        canPut = false;
                    }
                }

                if (canPut) {
                    for (int i = 0; i < ships[cur]; i++) {
                        state[r + i][c] = '1';
                    }
                    backtrack(cur + 1);
                    for (int i = 0; i < ships[cur]; i++) {
                        state[r + i][c] = '0';
                    }
                }
            }
        }
    }
}
int main()
{
    fast_cin();
    cin >> n >> k;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    ships.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> ships[i];
    }
    state.resize(n);
    for (int i = 0; i < n; i++) {
        state[i] = string(n, '0');
    }
    backtrack(0);
    cout << ans << endl;

    return 0;
}