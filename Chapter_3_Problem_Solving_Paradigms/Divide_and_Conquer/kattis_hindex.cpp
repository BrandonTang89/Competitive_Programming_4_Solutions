/**Kattis - hindex
 * Simple BSTA question. Just do it. Note that we speed things up slightly by sorting the array and
 * breaking early.
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
vector<int> v;

bool works(int h) {
    int ans = 0;
    for (auto i : v) {
        if (i >= h)
            ans++;
        else
            break;
    }
    return ans >= h;
}
int main() {
    fast_cin();
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end(), greater<int>());

    int l = 0, r = n;
    while (l + 1 < r) {
        int mid = (ll)(l + r) / 2;
        if (works(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    if (works(r)) {
        l = r;
    }
    cout << l << endl;
    return 0;
}