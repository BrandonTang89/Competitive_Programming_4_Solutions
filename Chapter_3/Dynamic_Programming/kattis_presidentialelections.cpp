/**Kattis - presidentialelections
 * DP with much pre-processing required. We only consider states that are not decided. Use some math
 * to determine the minimum number of voters we need to sway to win for each state and then at the
 * national level, how many delegates we need. If we can win and have not yet won, use DP knapsack
 * style to determine the minimum number of voters we need to sway. 
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

int n, cur_score, fo, ag, un, total_delegates = 0, del, unwon_del = 0;
const int INF = 1e9 + 9;
vector<int> states;
// states[i] = number of votes needed to convince i-th state, only positive values
vector<int> delegates;  // number of delegates
ll memo[2017][2017];
ll dp(int i, int needed) {  // returns the minimum number of voters needed
    if (needed <= 0) return 0;
    if (i == (int)states.size()) return INF;
    ll &ans = memo[i][needed];
    if (ans != -1) return ans;

    ans = min(dp(i + 1, needed), dp(i + 1, needed - delegates[i]) + states[i]);
    return ans;
}

int main() {
    fast_cin();
    cin >> n;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) {
        cin >> del >> fo >> ag >> un;
        total_delegates += del;
        if (fo > ag + un)
            cur_score += del;  // already won
        else if (fo + un <= ag)
            continue;  // unwinnable
        else {
            int needed = (ag - fo + un) / 2 + 1;
            unwon_del += del;
            states.push_back(needed);
            delegates.push_back(del);

            // cout << "needed: " << needed << endl;
        }
    }
    // cout << "cur score " << cur_score << endl;
    fo = cur_score;
    un = unwon_del;
    ag = total_delegates - fo - un;

    // cout << fo << " " << ag << " " << un << endl;
    if (fo > ag + un) {
        cout << 0 << endl;
        return 0;
    }
    if (fo + un <= ag) {
        cout << "impossible" << endl;
        return 0;
    }
    int needed = (ag - fo + un) / 2 + 1;
    // cout << needed << endl;
    cout << dp(0, needed) << endl;

    return 0;
}