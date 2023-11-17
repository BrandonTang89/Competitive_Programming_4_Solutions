/**Kattis - irrationaldivision
 * Mini-max with DP. Kinda a standardish problem. Just fiddling with the details on the numbers is
 * not ideal. We let the game state be (index of left column of remaining chocolate, index of bottom
 * row of remaining chocolate, player). This allows relatively easier evaluation of the value of
 * pieces taken away, but means that dealing with transitions is not uniform for both rows and
 * columns making it fiddly.
 * 
 * Time: O(hw*max(h,w)), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h, w;
vector<vector<vector<int>>> memo;

inline int eval(int r, int c, int r2, int c2)
{  // number of black - number of white squares in (r, c) to (r2, c2) rect inclusive
    if (abs(r - r2) % 2 == 1 && abs(c - c2) % 2 == 1) return 0;
    int x = (r + c) % 2 == 0 ? 1 : -1;
    int y = (r2 + c2) % 2 == 0 ? 1 : -1;
    return (x + y) / 2;
}

int dp(int leftcol, int bottomrow, int player)
{  // player == 0 if my turn, else sister turn
    // cout << leftcol << " " << bottomrow << " " << player << endl;
    if (leftcol == w || bottomrow == -1) return 0;
    if (memo[leftcol][bottomrow][player] != -1e9) return memo[leftcol][bottomrow][player];

    int ans;
    if (player == 0) {
        ans = -1e9;
        for (int re = leftcol + 1; re <= w; re++) {
            // take leftcol until re
            ans = max(ans, dp(re, bottomrow, 1) + (eval(0, leftcol, bottomrow, re - 1)));
        }
    }
    else {
        ans = 1e9;
        for (int be = -1; be < bottomrow; be++) {
            // take bottomrow until be
            ans = min(ans, dp(leftcol, be, 0) - eval(be + 1, leftcol, bottomrow, w - 1));
        }
    }
    return memo[leftcol][bottomrow][player] = ans;
}
int main()
{
    memo.assign(105, vector<vector<int>>(105, vector<int>(2, -1e9)));
    cin >> h >> w;
    cout << dp(0, h - 1, 0) << endl;

    return 0;
}