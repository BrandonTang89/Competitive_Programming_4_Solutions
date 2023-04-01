/**Kattis - ratings
 * Kinda a combi problem where we repeatedly use n choose k so the DP comes from memoizing that.
 * The math is "easy" to figure out. Just look at the code.
 *
 * Time: O(n^2), Mem: O(n^2) // for the DP table
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, t;
vector<int> ratings;

// dp n choose k
ll memo_comb[100][100];
ll comb(int n, int r)
{
    if (r == 0 || n == r) return 1;
    if (n < r) return 0;
    if (memo_comb[n][r] != -1) return memo_comb[n][r];
    return memo_comb[n][r] = comb(n - 1, r - 1) + comb(n - 1, r);
}

ll rec(int i, ll k)
{  // returns the number of ways, assuming that the ratings for our constructed restaurant[0, i) are
   // the same as the original ratings[0, i) and we are putting k more rating points overall.
    if (i == n) {
        return (k == 0);
    }

    ll ans = rec(i + 1, k - ratings[i]);
    for (int j = 0; j < ratings[i]; j++) {
        ans += comb(k - j + n - i - 2, k - j);  // distribution problem
    }
    return ans;
}
int main()
{
    memset(memo_comb, -1, sizeof(memo_comb));
    while (true) {
        cin >> n;
        if (n == 0) break;
        ratings.assign(n, 0);
        t = 0;
        for (int i = 0; i < n; i++) {
            cin >> ratings[i];
            t += ratings[i];
        }

        ll ans = 0;
        for (int j = 0; j < t; j++) {
            ans += comb(n + j - 1, n - 1);  // distribution problem
        }
        ans += rec(0, t);
        cout << ans << endl;
    }

    return 0;
}