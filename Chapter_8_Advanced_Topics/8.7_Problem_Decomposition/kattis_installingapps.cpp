/**Kattis - installingapps
 * DP + Greedy + Printing Solution.
 * The first step is to partition the apps into 2 classes, one where dbs (d > s) and the other dss
 * where (d <= s). Now, suppose we have selected a set of apps to install. Clearly we should install
 * the apps in dbs first rather than the apps in dss. This can be seen by swapping the order of
 * install of 2 adjacent apps where the first is a dss and the second is a dbs. Clearly the new
 * ordering will also work.
 *
 * Next, we notice that when we decide that we have taken enough dbs apps, the optimal set of dss
 * apps to take is attained by repeatedly taking the smallest dbs app. This can be seen by
 * observation that given some optimal selection of dss apps, we can always do the same or better to
 * swap out a larger app for a smaller app. As such, we can precompute the number of dss apps we can
 * have for each amount of space left in O(n log n + c) time (n log n to sort).
 *
 * For selecting the dbs apps, we note that we need to do a DP. But the order of the apps matters.
 * It requires some observation to notice that ordering in decreasing (d-s) is optimal...I.e.
 * suppose we have a set of dbs apps, if there exist a valid ordering of them, decreasing (d-s) will
 * also be valid. Work it out on a paper: do an exchange argument where swapping 2 adjacent apps in
 * an inversion will still be valid.
 *
 * Now we can just do a DP to select apps from dbs in order of decreasing (d-s). At each step, we
 * either skip the current app, take it, or stop taking dbs apps entirely (go to take from dss).
 *
 * Printing the solution is relatively trivial. Just do a linear recursive function that traces the
 * transitions of the DP.
 *
 * Time: O(nc), Space: O(nc).
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, c;
vector<tuple<int, int, int>> dbs, dss;
vector<int> precomp;

bool custom_comp(tuple<int, int, int> a, tuple<int, int, int> b)
{
    auto &[d1, s1, i1] = a;
    auto &[d2, s2, i2] = b;
    return (d1 - s1) > (d2 - s2);
}

vector<vector<int>> memo;
int dp(int i, int space)
{
    if (i == (int)dbs.size()) return precomp[space];
    if (memo[i][space] != -1) return memo[i][space];

    auto &[d, s, idx] = dbs[i];
    int ans = max(dp(i + 1, space), precomp[space]);
    if (space >= d) ans = max(ans, dp(i + 1, space - s) + 1);
    return memo[i][space] = ans;
}

void print_sol2(int space)
{
    int cur_size = 0;
    for (int i = 0; i < (int)dss.size(); i++) {
        cur_size += get<0>(dss[i]);
        if (cur_size > space) break;
        cout << get<2>(dss[i]) + 1 << " ";
    }
    cout << endl;
}

void print_sol(int i, int space)
{
    if (i == (int)dbs.size()) {
        print_sol2(space);
        return;
    }

    if (dp(i, space) == dp(i + 1, space)) {
        print_sol(i + 1, space);
        return;
    }

    if (dp(i, space) == precomp[space]) {
        print_sol2(space);
        return;
    }

    auto &[d, s, idx] = dbs[i];
    assert(space >= d && dp(i, space) == dp(i + 1, space - s) + 1);
    cout << idx + 1 << " ";
    print_sol(i + 1, space - s);
}

int main()
{
    fast_cin();
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int d, s;
        cin >> d >> s;
        if (d > s)
            dbs.push_back({d, s, i});
        else
            dss.push_back({s, d, i});
    }
    precomp.assign(c + 1, 0);
    sort(dss.begin(), dss.end());
    dss.push_back({c + 1, c + 1, -1});
    int cur_size = 0;
    for (int i = 0; i < (int)dss.size(); i++) {
        int prev_size = cur_size;
        if (cur_size + get<0>(dss[i]) > c) {
            for (int j = prev_size; j <= c; j++) {
                precomp[j] = i;
            }
            break;
        }
        cur_size += get<0>(dss[i]);
        for (int j = prev_size; j < cur_size; j++) {
            precomp[j] = i;
        }
    }
    sort(dbs.begin(), dbs.end(), custom_comp);

    memo.assign(dbs.size(), vector<int>(c + 1, -1));
    cout << dp(0, c) << endl;
    print_sol(0, c);

    return 0;
}