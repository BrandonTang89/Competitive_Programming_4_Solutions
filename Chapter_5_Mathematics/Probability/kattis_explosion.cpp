/**Kattis - explosion
 * DP with base 7 bitmask. Let dp(d, mine, opp) be the probability of eliminating all the opponent's
 * minions with d damage left. We can then transition by considering all possible distributions of
 * the damage. We do a lot of pruning by ensuring that the encoding is done after sorting the vector
 * and we only try damaging 1 minion out of all minions of the same health (within my hand and my
 * opp's hand separately), though we need to modify the probability calculation with the counter.
 *
 * Since not that much of the state space is actually used, an array would MLE so we just use a
 * balanced binary search tree for the memo table.
 * 
 * Time: O(not easy to calculate), Space: O(not easy to calculate)
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

int encode(vector<int> &arr)
{
    int ans = 0;
    int factor = 1;
    sort(arr.begin(), arr.end(), greater<int>());
    for (int i = 0; i < (int)arr.size(); i++) {
        ans += factor * (arr[i]);
        factor *= 7;
    }
    return ans;
}

vector<int> decode(int mask)
{
    vector<int> ans;
    while (mask > 0) {
        ans.push_back(mask % 7);
        mask /= 7;
    }
    return ans;
}

// double memo[101][16807][16807];
map<tuple<int, int, int>, double> memo;
double dp(int d, int mine, int opp)
{
    if (opp == 0) return 1;  // no more opp;
    if (d == 0) return 0;

    if (memo.find({d, mine, opp}) != memo.end()) return memo[{d, mine, opp}];

    vector<int> myMask = decode(mine);
    vector<int> oppMask = decode(opp);

    int n = myMask.size() + oppMask.size();
    double ans = 0;
    int counter = 1;
    for (int i = 0; i < (int)myMask.size(); i++) {
        if (i < (int)myMask.size() - 1 && myMask[i + 1] == myMask[i]) {
            counter++;
            continue;
        }
        myMask[i]--;
        bool poped = false;
        if (myMask[i] == 0) {
            assert(i == (int)myMask.size() - 1);
            myMask.pop_back();
            poped = true;
        }
        ans += dp(d - 1, encode(myMask), opp) * counter / (double)n;
        if (poped) myMask.push_back(0);
        myMask[i]++;
        counter = 1;
    }
    for (int i = 0; i < (int)oppMask.size(); i++) {
        if (i < (int)oppMask.size() - 1 && oppMask[i + 1] == oppMask[i]) {
            counter++;
            continue;
        }
        oppMask[i]--;
        bool poped = false;
        if (oppMask[i] == 0) {
            assert(i == (int)oppMask.size() - 1);
            oppMask.pop_back();
            poped = true;
        }
        ans += dp(d - 1, mine, encode(oppMask)) * counter / (double)n;
        if (poped) oppMask.push_back(0);
        oppMask[i]++;
        counter = 1;
    }
    return memo[make_tuple(d, mine, opp)] = ans;
}
int main()
{
    fast_cin();
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> myMask(n, 0);
    vector<int> oppMask(m, 0);

    for (int i = 0; i < n; i++) {
        cin >> myMask[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> oppMask[i];
    }
    cout << fixed << setprecision(12) << dp(d, encode(myMask), encode(oppMask)) << endl;
    return 0;
}