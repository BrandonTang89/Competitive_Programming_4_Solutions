/**Kattis - wherehaveyoubin
 * We should start with doing all the delete and add operations to see which bins are left and how
 * many bins each of the companies require.
 *
 * Let dp(bm, i) be the minimum cost assuming the next available bin is i and we still need to deal
 * with companies {j | jth bit of bm is set}. We either skip this bin over (leave empty) or we try
 * using each company now, and filling in a run of bins. Just take the min cost of all these
 * options.
 * 
 * Time: O(2^5 * n^2), Space: O(2^5 * n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) (S & (-S))
int n;
vector<int> owner;
vector<int> v;
unordered_map<char, int> mp;

vector<vector<int>> memo;
vector<int> num_bins;  // number of bins for each vowel
int dp(int bm, int i)
{  // minimum cost assuming the next available bin is i
    assert(i <= n);
    if (i == n) return (bm == 0 ? 0 : 1e6);
    if (memo[bm][i] != -1) return memo[bm][i];

    int ans = 1e6;

    int ibm = bm;
    while (ibm) {
        int cur = __builtin_ctz(ibm);

        if (i + num_bins[cur] - 1 >= n) {
            return memo[bm][i] = 1e6;  // not enough bins left
        }
        int cost = 0;
        for (int j = 0; j < num_bins[cur]; j++) {
            if (owner[i + j] == cur) continue;
            cost += v[i + j];  // kick out all these bins
        }
        cost += dp(bm ^ (1 << cur), i + num_bins[cur]);
        ans = min(ans, cost);
        ibm -= LSOne(ibm);
    }
    ans = min(ans, dp(bm, i + 1) + v[i]);  // skip this bin over, pay for removing v[i]
    return memo[bm][i] = ans;
}
int main()
{
    mp['X'] = -1;
    mp['A'] = 0;
    mp['E'] = 1;
    mp['I'] = 2;
    mp['O'] = 3;
    mp['U'] = 4;

    string s;
    cin >> s;
    n = s.size();
    v.resize(n);
    owner.resize(n);
    num_bins.assign(5, 0);
    for (int i = 0; i < n; i++) {
        owner[i] = mp[s[i]];

        if (owner[i] != -1) num_bins[owner[i]]++;
        cin >> v[i];
    }

    int num_del;
    cin >> num_del;
    for (int i = 0; i < num_del; i++) {
        int x;
        cin >> x;
        x--;
        v[x] = 0;  // remove all the materials
        num_bins[owner[x]]--;
        owner[x] = -1;  // remove the owner
    }

    cin >> s;
    for (auto c : s) {
        if (c == 'X') break;
        num_bins[mp[c]]++;
    }

    memo.resize(1 << 5, vector<int>(n + 1, -1));
    cout << dp((1 << 5) - 1, 0) << endl;

    return 0;
}