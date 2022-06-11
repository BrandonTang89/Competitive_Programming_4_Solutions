/**Kattis - manhattanmornings
 * Kinda okay LNDS problem. First we assume that the start is to the bottom left of the end, else we
 * can apply flips on one or both axes to make it so. Now we can sort the locations by x and then y
 * coordinate and then take the LNDS of the y values in the sorted array. Notice that this is valid
 * because the y values will be non-decreasing (by definition of LNDS) while the x values are also
 * non-decreasing as we had first sorted the locations by x then y.
 *
 * Time: O(n log n), Space: O(n)
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

int n;
int main() {
    cin >> n;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    bool flipx = (sx > ex), flipy = (sy > ey);

    if (flipx) {
        sx = -sx;
        ex = -ex;
    }
    if (flipy) {
        sy = -sy;
        ey = -ey;
    }
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (flipx) x = -x;
        if (flipy) y = -y;

        if (sx > x || sy > y || ex < x || ey < y) {
            continue;
        }
        arr.push_back({x, y});
    }

    n = arr.size();
    sort(arr.begin(), arr.end());
    vector<int> v;
    for (auto i : arr) v.emplace_back(i.second);
    vector<int> L(n, 0);  // L[i] is the minimum last element of an NDS of length i
    int k = 0;            // length of current LNDS
    for (int i = 0; i < n; i++) {
        int pos = upper_bound(L.begin(), L.begin() + k, v[i]) - L.begin();
        L[pos] = v[i];
        if (pos == k) {
            k++;
        }
    }
    cout << k << endl;

    return 0;
}