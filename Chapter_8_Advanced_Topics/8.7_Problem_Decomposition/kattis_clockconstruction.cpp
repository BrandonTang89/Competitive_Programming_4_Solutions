/**Kattis - clockconstruction
 * Relatively cool problem. For each pixel, record whether it needs to be on or off in image i as a
 * 1 or 0 bit in a n digit long bit mask. Since we don't have 100 bit integers (easily), then we use
 * a pair of 64 bit integers.
 *
 * At the end, just see how many unique pairs we have using a set.
 *
 * Time: O(nhw log hw), Mem: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, h, w;
inline int coord(int r, int c) { return r * w + c; }
vector<pair<ll, ll>> bms;
set<pair<ll, ll>> seen;
int main()
{
    cin >> n >> h >> w;
    bms.assign(h * w, {0LL, 0LL});
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                char x;
                cin >> x;
                if (x == '*') {
                    if (i < 64) {
                        bms[coord(r, c)].first |= (1LL << i);
                    }
                    else {
                        bms[coord(r, c)].second |= (1LL << (i - 64));
                    }
                }
            }
        }
    }
    for (auto i : bms) seen.insert(i);
    cout << seen.size() << endl;

    return 0;
}