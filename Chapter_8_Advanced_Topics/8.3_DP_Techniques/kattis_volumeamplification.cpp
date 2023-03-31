/**Kattis - volumeamplification
 * Relatively simple DP, some optimisations. First we sort the speakers so can "stop early" if the
 * next speaker is too big already. Let dp(vol, index) be the minimum volume difference between the
 * end result assuming we are at volume vol and the next speaker to consider is index. So we either
 * take the speaker or don't take (kinda like knapsack).
 * Now, the main optimisation to make is that if we get to dp(vol, index) but we have previously
 * calculated dp(vol, index') for some index' < index, then we can just terminate now since we have
 * already calculated a potentially better answer since the answer for dp(vol, index') must be at
 * least as good as that of dp(vol, index) since the speakers we have to choose from are a superset
 * of the speakers we have to choose from for dp(vol, index). This also helps to reduce the memory
 * consumption since we only need to store the minimum index we have calculated for each volume and
 * the answer.
 * 
 * Time: O(? better than O(yn)), Space: O(y)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, y;
vector<int> memo1;  // minimum index that reached this volume
vector<ll> memo2;   // the outcome of that index at this volume
vector<ll> v;

ll dp(ll vol, int index)
{
    if (index == n) return (y - vol);
    if (memo1[vol] != -1) {
        if (memo1[vol] <= index) {
            return 1e9;  // don't bother doing this one
        }
    }
    ll ans = y - vol;
    if (vol * v[index] <= y) {  // only recurse if it's possible to improve
        ans = min(dp(vol, index + 1), dp(vol * v[index], index + 1));
    }
    memo1[vol] = index;
    memo2[vol] = ans;
    return ans;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> y;
        memo1.assign(y + 1, -1);
        memo2.assign(y + 1, 1e9);
        v.assign(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        sort(v.begin(), v.end());

        cout << y - dp(1, 0) << endl;
    }

    return 0;
}