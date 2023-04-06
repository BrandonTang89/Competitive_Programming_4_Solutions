/**Kattis - tugofwar
 * A variant of the partition problem (partition a set into two subsets such that the difference is
 * minimised) except the sizes of the subsets must not differ by more than 1. On iniital inspection,
 * we may be worried about TLE because the number of states is O(450*n^3). However, we note that
 * num_less and num_more (the number of elements in the smaller than larger (in terms of sum)) are
 * bounded by ceil(n/2). As such, diff is also bounded by 450*ceil(n/2). This means that the
 * straightforward dp (recovering the index of the next position to consider by adding num_less +
 * num_more) will not TLE.
 *
 * So we let dp(diff, num_less, num_more) be the minimum difference we can achieve.
 * 
 * Time: O(450*(n/2)^3) = O(n^3), Mem: O(n^3)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
int stop;
vector<int> v, pref_sum;
vector<vector<vector<int>>> memo;
int dp(int diff, int num_less, int num_more)
{
    int nex = num_less + num_more;
    if (nex == n) {
        return diff;
    }
    if (memo[diff][num_less][num_more] != -1) {
        return memo[diff][num_less][num_more];
    }

    if (num_less == stop) {
        return memo[diff][num_less][num_more] = diff + pref_sum[n - 1] - pref_sum[nex - 1];
    }
    if (num_more == stop) {
        return memo[diff][num_less][num_more] = abs(diff - pref_sum[n - 1] + pref_sum[nex - 1]);
    }

    int ans = INT_MAX;
    ans = min(ans, dp(diff + v[nex], num_less, num_more + 1));
    if (diff - v[nex] >= 0) {
        ans = min(ans, dp(diff - v[nex], num_less + 1, num_more));
    }
    else {
        ans = min(ans, dp(abs(diff - v[nex]), num_more, num_less + 1));
    }
    return memo[diff][num_less][num_more] = ans;
}
int main()
{
    cin >> n;
    v.resize(n);
    pref_sum.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        pref_sum[i] = v[i] + (i == 0 ? 0 : pref_sum[i - 1]);
    }
    stop = (n + 1) / 2;
    memo.resize(450 * (stop + 1), vector<vector<int>>(stop + 1, vector<int>(stop + 1, -1)));

    int diff = dp(0, 0, 0);
    int lef = (pref_sum[n - 1] - diff) / 2;
    int rig = pref_sum[n - 1] - lef;
    cout << lef << " " << rig << endl;

    return 0;
}