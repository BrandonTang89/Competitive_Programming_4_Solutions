/**Kattis - unicycles
 * Math + DP. We let dp(bm) be the number of unicycles needed to cover all markings in bm, our
 * answer is dp((1 << n) - 1) to cover all the markings.
 *
 * For each dp(bm), we try to cover the left-most marking in bm. We do this by trying all possible
 * periods and checking if they are valid (assuming they cover the left-most marking). If so, we
 * have a candidate unicycle to take. dp(bm) = min(dp(new_bm) + 1) for all new_bm from all possible
 * periods that cover the leftmost marking in bm.
 *
 * Also note that the input can come unsorted, so we need to sort it first (potential debugging
 * trap).
 *
 * Time: O(2^n * m^2), Space: O(2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) (S & (-S))
int n, m;
vector<int> memo, v;
unordered_set<int> marks;
int dp(int bm)  // minimum unicycles to cover all markings in bm
{
    int &ans = memo[bm];
    if (ans != -1) return ans;
    if (bm == 0) return ans = 0;

    int cur = __builtin_ctz(LSOne(bm));  // we deal with this left-most marking

    ans = INT_MAX;
    for (int i = 1; i <= m; i++) {  // check all periods
        int new_bm = bm;
        bool possible = true;
        for (int j = v[cur]; j < m && possible; j += i) {  // check if this period is possible
            if (marks.count(j)) {
                int idx = lower_bound(v.begin(), v.end(), j) - v.begin();  // get index of marking
                new_bm &= (~(1 << idx));  // we have covered this marking
            }
            else {
                possible = false;
            }
        }
        for (int j = v[cur]; j >= 0 && possible; j -= i) {
            if (!marks.count(j)) {
                possible = false;
            }
        }
        if (!possible) continue;
        assert(new_bm != bm);  // we must have rolled over at least cur
        ans = min(ans, dp(new_bm) + 1);
    }
    assert(ans != INT_MAX);
    return ans;
}
int main()
{
    while (cin >> m >> n) {
        memo.assign(1 << n, -1);
        v.assign(n, 0);
        marks.clear();
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            marks.insert(v[i]);
        }
        sort(v.begin(), v.end());
        cout << dp((1 << n) - 1) << endl;
    }

    return 0;
}