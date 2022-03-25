/**kattis - countcircuits
 * An actually relatively simple problem. We just practise the offset technique here to avoid negative indices. We
 * note that the lowest value of x and y is -400 by having 40*-10.
 * 
 * Time: O(n*800*800), Space: O(n*800*800)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n;
ll OFFSET = 400;
vector<pair<ll, ll>> vectors;

ll memo[41][809][809];
ll dp(ll index, ll x, ll y) {
    if (index == n) return (x == 0 && y == 0);
    if (memo[index][x + OFFSET][y + OFFSET] != -1) return memo[index][x + OFFSET][y + OFFSET];

    return memo[index][x + OFFSET][y + OFFSET] =
               dp(index + 1, x + vectors[index].first, y + vectors[index].second) +
               dp(index + 1, x, y);
}

int main() {
    cin >> n;
    vectors.resize(n);
    ll x, y;
    for (ll i = 0; i < n; i++) {
        cin >> x >> y;
        vectors[i] = {x, y};
    }
    memset(memo, -1, sizeof memo);
    cout << dp(0, 0, 0) - 1 << endl;

    return 0;
}