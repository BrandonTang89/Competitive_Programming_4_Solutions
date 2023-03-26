/**Kattis - homework
 * Relatively simple DP, I'm not sure why this is high difficulty on Kattis. Let dp(i, j) be the
 * value "we can fit a[i:], b[j:] into s[i+j:]". This is an example of recovering the parameter of
 * the location in s that we are considering...
 *
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

string s, a, b;
vector<vector<int>> memo;
bool dp(int i, int j)
{
    if (memo[i][j] != -1) return memo[i][j];
    if (i == (int)a.size() && j == (int)b.size()) return (memo[i][j] = 1);  // basecase: we are done
    if (i == (int)a.size()) {                                               // no more from a
        return (memo[i][j] = (s[i + j] == b[j] && dp(i, j + 1)));
    }
    if (j == (int)b.size()) {  // no more from b
        return (memo[i][j] = (s[i + j] == a[i] && dp(i + 1, j)));
    }

    return (memo[i][j] =  // try fitting both
            ((s[i + j] == a[i] && dp(i + 1, j)) || (s[i + j] == b[j] && dp(i, j + 1))));
}
int main()
{
    cin >> s >> a >> b;
    memo.assign(a.size() + 1, vector<int>(b.size() + 1, -1));
    cout << (dp(0, 0) ? "yes" : "no") << endl;

    return 0;
}