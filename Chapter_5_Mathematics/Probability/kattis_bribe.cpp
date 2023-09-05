/**Kattis - bribe
 * Kinda interesting dp with bitmask problem. The key observation for this problem is that
 * we can bribe the people in any order, so we maintain a bitmask of the people we can still attempt
 * to bribe and then we take the max probability of success of attempting to bribe any available
 * person.
 *
 * The naive dp state is (number of people need to bribe, bitmask of available people, money left),
 * but this will MLE. We can actually recover the money left parameter by starting with m and
 * subtracting the cost of the people that we already tried to bribe (which is recovered from the
 * bitmask).
 *
 * Time: O(n^2 * 2^n), Space: O(n*2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

int n, m;
double memo[17][1 << 16];
vector<double> ps;
vector<int> bs;
double dp(int c, int bm) // probability of getting c people given bitmask of available people
{
    if (memo[c][bm] != -1) return memo[c][bm];
    if (__builtin_popcount(bm) < c) return 0;  // not enough people left to bribe
    if (c == 0) return 1;                      // finished bribing

    double ans = 0;
    int mask = bm;
    int money = m;
    for (int i = 0; i < n; i++) {
        if (!(bm & (1 << i))) money -= bs[i];
    }
    while (mask > 0) {
        int selected = __builtin_ctz(mask);
        mask ^= (1 << selected);
        if (money < bs[selected]) continue;
        ans = max(ans, ps[selected] * dp(c - 1, bm ^ (1 << selected)) +
                           (1 - ps[selected]) * dp(c, bm ^ (1 << selected)));
    }
    return memo[c][bm] = ans;
}

int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        memset(memo, -1, sizeof memo);
        int c;
        cin >> n >> c >> m;
        ps.assign(n, 0);
        bs.assign(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> bs[i] >> ps[i];
            ps[i] /= 100.0;
        }
        cout << fixed << setprecision(12) << dp(c, (1 << n) - 1) << endl;
    }

    return 0;
}