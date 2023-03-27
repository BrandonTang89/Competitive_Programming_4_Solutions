/**Kattis - welcomehard
 * Relatively basic DP. Let dp(i, k) be the number of subsequences in text[i:] that we can match to
 * the pattern[k:].
 * 
 * Time: O(NM), Mem: O(NM)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int MOD = 1e4;
string pattern = "welcome to code jam";
string text;
int n, m;

vector<vector<int>> memo;

int dp(int i, int k)
{  // we are at position i and we are looking for the kth character of the pattern
    if (k == m) return 1;
    if (i == n) return 0;

    int &ans = memo[i][k];
    if (ans != -1) return ans;

    if (text[i] == pattern[k])
        ans = (dp(i + 1, k + 1) + dp(i + 1, k)) % MOD;
    else
        ans = dp(i + 1, k);

    return ans;
}
int main()
{
    int tc;
    cin >> tc;
    cin.ignore();
    m = pattern.size();

    for (int t = 1; t <= tc; t++) {
        getline(cin, text);
        n = text.size();
        memo.assign(n + 1, vector<int>(m + 1, -1));
        cout << "Case #" << t << ": ";
        cout << setfill('0') << setw(4) << dp(0, 0) << endl;
    }

    return 0;
}