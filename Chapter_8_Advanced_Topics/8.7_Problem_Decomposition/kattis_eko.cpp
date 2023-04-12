/**Kattis - eko
 * Essentially adhoc. We sort the list in descending order then traverse from left to right, taking
 * candidate heights to be the height of each tree (v[i]). When going from 1 candidate height to the
 * next, the increase in wood we attain is (v[i-1] - v[i]) * i. We keep track of the total wood we
 * have attained so far. If delta_wood + wood_attained < s, we can continue to the next candidate
 * height. Otherwise, the height is somewhere between the current height and the height of the last
 * tree. We use math to attain the height. We shoud also add a dummy 0 height tree to make the code
 * neater.
 * 
 * Time: O(n log n), Mem: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
ll s;
vector<ll> v;
int main()
{
    fast_cin();
    cin >> n >> s;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    v.emplace_back(0);
    sort(v.begin(), v.end(), greater<ll>());

    ll wood_attained = 0;
    for (int i = 1; i < n + 1; i++) {
        ll delta_wood = (v[i - 1] - v[i]) * i;
        if (delta_wood + wood_attained < s) {
            wood_attained += delta_wood;
            continue;
        }

        // dh = ceil((s - wood_attained) / i) [minimum decrease in height to attain s wood]
        ll dh = (s - wood_attained + i - 1) / i;
        cout << v[i - 1] - dh << endl;
        return 0;
    }

    return 0;
}