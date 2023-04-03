/**Kattis - uxuhulvoting
 * Let dp(bm, v) be the outcome assuming the voter v votes when the stones are in the state bm. We
 * just check dp(nbm, v+1) for each 3 possible new states that can be reached from bm and select the
 * state that is the most preferable for voter v.
 * 
 * Time: O(2^3 * n), Mem: O(2^3 * n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> preferences;  // preferences[i][outcome] = rank of outcome for voter i
vector<vector<int>> memo;
int dp(int bm, int v)
{
    if (v == n) return bm;
    if (memo[bm][v] != -1) return memo[bm][v];

    // voter can flip one of the stones
    int ans = -1;
    int anspref = 1e8;
    for (int i = 0; i < 3; i++) {
        int nbm = bm ^ (1 << i);
        assert(nbm != bm);
        int cur = dp(nbm, v + 1);
        if (preferences[v][cur] < anspref) {
            anspref = preferences[v][cur];
            ans = cur;
        }
    }
    return memo[bm][v] = ans;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        preferences.assign(n, vector<int>(8, -1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> preferences[i][j];
            }
        }

        memo.assign(8, vector<int>(n, -1));
        int ans = dp(0, 0);
        for (int i = 2; i >= 0; i--) {
            cout << ((ans & (1 << i)) ? 'Y' : 'N');
        }
        cout << endl;
    }

    return 0;
}