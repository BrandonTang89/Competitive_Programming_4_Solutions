/**Kattis - wordcloud
 * A problem that requires good selection of state! I previously selected to use the state as
 * (index, current height, current width) with the transition to either put words[index] in the
 * current line or to make a new line. This is too slow with a complexity of O(n*wl*150)! Notice
 * instead that if we use the state as just (index) but with the transition to try all valid lines
 * that start with words[index] all the way until some word such that the line is too long, we have
 * transition time as O(n) resulting in O(n^2) solution which is superior.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, wl;  // num words, width limit

vector<pair<int, int>> words;
int memo[5009];
int dp(int cur) {
    if (cur == n) return 0;
    if (memo[cur] != -1) return memo[cur];
    int cw = 0, ch = 0;
    int ans = 1e9;
    for (int i = cur; i < n; i++) {
        cw += words[i].first;
        ch = max(ch, words[i].second);
        if (cw > wl) break;
        ans = min(ans, dp(i + 1) + ch);
    }
    return memo[cur] = ans;
}
int main() {
    cin >> n >> wl;
    words.resize(n);
    for (int i = 0; i < n; i++) {
        int w, h;
        cin >> w >> h;
        words[i] = {w, h};
    }
    memset(memo, -1, sizeof memo);
    cout << dp(0) << endl;

    return 0;
}