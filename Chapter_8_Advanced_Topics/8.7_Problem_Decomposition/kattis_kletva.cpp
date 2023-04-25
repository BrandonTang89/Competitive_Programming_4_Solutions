/**Kattis - kletva
 * Equivalance check of the keys. We have to deal with translation (easy) and rotation (turn 180
 * degrees) in 2 axes (harder). The idea is we keep a set of pairs that represent all the possible
 * rotations of all keys we have already seen. Then for each new key, we insert all 4 possible
 * rotations of the key into the set. This just requires abit of adhoc logic.
 * 
 * Time: O(ln log n), Space: O(ln)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int w, l, n;
set<pair<vector<int>, vector<int>>> s;
int main()
{
    cin >> w >> l >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> top(l), bot(l);
        int mini = INT_MAX;
        for (int j = 0; j < l; j++) {
            cin >> top[j];
            mini = min(mini, top[j]);
        }
        for (int j = 0; j < l; j++) {
            top[j] -= mini;
        }
        for (int j = 0; j < l; j++) {
            cin >> bot[j];
            bot[j] += mini;
        }

        if (s.find({top, bot}) != s.end()) continue;  // if already exists, skip
        ans += 1;
        s.insert({top, bot});
        reverse(top.begin(), top.end());
        reverse(bot.begin(), bot.end());
        s.insert({top, bot});

        mini = INT_MAX;
        for (int j = 0; j < l; j++) {
            swap(top[j], bot[j]);
            mini = min(mini, top[j]);
        }
        for (int j = 0; j < l; j++) {
            top[j] -= mini;
            bot[j] += mini;
        }
        s.insert({top, bot});
        reverse(top.begin(), top.end());
        reverse(bot.begin(), bot.end());
        s.insert({top, bot});
    }
    cout << ans << endl;

    return 0;
}