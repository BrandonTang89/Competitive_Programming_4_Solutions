/**Kattis - balanceddiet
 * Somewhat like a subset sum problem. We can use DP to help us achieve pseudo-polynomial time.
 * Let dp(left, i) be the best outcomes assuming that the first i items are already been allocated
 * and we have the lower sum has value left. We can either put the i-th item into the left or into
 * the right pile. We try those and then we take the best outcome.
 *
 * Time: O(total_sum * n), Mem: O(total_sum * n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, total;
vector<int> a;
vector<vector<tuple<int, int>>> memo;
tuple<int, int> dp(int left, int i)
{
    if (i == n) return {left, total - left};
    if (memo[left][i] != make_tuple(-1, -1)) return memo[left][i];

    // either put into left or into right
    tuple<int, int> c1 = dp(left + a[i], i + 1);
    tuple<int, int> c2 = dp(left, i + 1);

    int l1 = get<0>(c1), l2 = get<0>(c2);
    int r1 = get<1>(c1), r2 = get<1>(c2);

    if (l1 <= r1 && l2 <= r2) {
        if (r1 - l1 < r2 - l2)
            return memo[left][i] = c1;
        else
            return memo[left][i] = c2;
    }
    else if (l1 <= r1)
        return memo[left][i] = c1;
    else if (l2 <= r2)
        return memo[left][i] = c2;
    else
        return memo[left][i] = c1;  // return anything cos it's impossible
}
int main()
{
    while (1) {
        cin >> n;
        if (n == 0) break;

        a.resize(n);
        total = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            total += a[i];
        }
        memo.assign(total + 1, vector<tuple<int, int>>(n, {-1, -1}));
        tuple<int, int> ans = dp(0, 0);
        cout << get<1>(ans) << " " << get<0>(ans) << endl;  // we eat the one with more first
    }

    return 0;
}