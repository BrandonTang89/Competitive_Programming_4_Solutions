/**Kattis - mububa
 * Relatively straightforward DP but with some non-trivial optimisations. Let dp(prev, cur) be the
 * max possible number of employees we can satisfy assuming that the previous employee got the
 * briefcases [prev, cur) (so the next employee will get at most briefcases [cur, n)).
 *
 * dp(prev, n) = 0 // base case
 * dp(prev, cur) =
 *  if rsq(cur, n-1) < rsq(prev, cur-1): 0 // if the next employee can't get enough
 *  otherwise: 1 + max(dp(cur, k+1)) for all k such that rsq(cur, k) >= rsq(prev, cur-1)
 *
 * Now using a direct memo such that memo[i][j] = dp(i, j) will be TLE since the state space is
 * O(n^2) and the transition would be O(n). However, we can do better by noticing that max(dp(cur,
 * k+1)) takes the max of a contiguous segment of the memo array (dp(cur, l+1), dp(cur, l+2), ...,
 * dp(cur, n)) for some l such that l is the smallest element that satisfies rsq(cur, l) >=
 * rsq(prev, cur-1).
 *
 * As such, we can use memo[i][j] = max(dp(i, k) for j <= k <= n) = max(dp(i, j), memo[i][j+1])
 * assuming that we fill in the tmemo table in (decreasing i, decreasing j).
 *
 * Now the question remains to find the first l such that rsq(cur, l) >= rsq(prev, cur-1). Observe
 * that we can binary search for l since rsq(cur, l) is a monotonically increasing function of l.
 * Since we use static range sum queries, we can do this binary search in O(log n).
 *
 * The last detail is that to actually get the answer we need, we should add a dummy briefcase with
 * 0 bananas at the front. Then our answer will be dp(0, 1) which means that the first employee can
 * receive >= 0 bananas (but will receive at least 1) and starts from the briefcase 1 (the first
 * non-dummy briefcase). This is why we add 1 to n in the code.
 * 
 * Time: O(n^2 log n), Space: O(n^2)
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

typedef long long ll;
int memo[3001][3001];

int n;
vector<ll> arr;
inline ll rsq(int l, int r)
{  // range sum from l to r inclusively
    assert(l >= 0 && r < n);
    if (l == 0) return arr[r];
    return (arr[r] - arr[l - 1]);
}

int main()
{
    fast_cin();
    cin >> n;
    n++;
    arr.resize(n);
    arr[0] = 0;
    for (int i = 1; i < n; i++) {
        cin >> arr[i];
        if (i > 0) arr[i] += arr[i - 1];
    }

    for (int prev = n - 1; prev >= 0; prev--) {
        for (int cur = n - 1; cur >= prev + 1; cur--) {
            ll mini = rsq(prev, cur - 1);
            int ans;
            if (rsq(cur, n - 1) >= mini) {
                int l = cur;
                int r = n - 1;

                // We are trying to find the first value k such that rsq(cur, k) >= mini
                while (l < r) {
                    int mid = (l + r) / 2;
                    if (rsq(cur, mid) >= mini)
                        r = mid;
                    else
                        l = mid + 1;
                }

                // l is the first value such that rsq(cur, l) >= mini
                ans = 1 + memo[cur][l + 1];
            }
            else
                ans = 0;
            memo[prev][cur] = max(memo[prev][cur + 1], ans);
        }
    }

    cout << memo[0][1] << endl;

    return 0;
}