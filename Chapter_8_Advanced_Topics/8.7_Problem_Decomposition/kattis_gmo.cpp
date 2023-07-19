/**Kattis - gmo
 * DP + String Processing. Surprisingly simple question, we just try matching starting from all
 * possible positions. Note that if we match, it is always beneficial to just use that character,
 * if we don't match then the only move is to insert another character. The reason we need to DP
 * is that we are looking to find the minimum across all dp(0, i) so we should avoid recomputing.
 *
 * Time: O(nm) {though i theorise that a lot of state space may not be reached}
 * Space: O(nm)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

string dna, gene;
int n, m;
vector<vector<int>> memo;
unordered_map<char, int> cost;
int dp(int genei, int dnai)
{
    if (memo[genei][dnai] != -1) return memo[genei][dnai];
    if (genei == m) return memo[genei][dnai] = 0;  // done
    if (dnai == n) {
        int ans = 0;
        for (int i = genei; i < m; i++) {
            ans += cost[gene[i]];
        }
        return memo[genei][dnai] = ans;
    }

    if (dna[dnai] == gene[genei])
        return memo[genei][dnai] = dp(genei + 1, dnai + 1);
    else
        return memo[genei][dnai] = dp(genei + 1, dnai) + cost[gene[genei]];
}
int main()
{
    cin >> dna >> gene;
    cin >> cost['A'] >> cost['C'] >> cost['G'] >> cost['T'];
    n = dna.size();
    m = gene.size();
    memo.assign(m + 1, vector<int>(n + 1, -1));

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp(0, i));
    }
    cout << ans << endl;
    return 0;
}