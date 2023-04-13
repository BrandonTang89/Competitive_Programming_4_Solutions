/**Kattis - ozljeda
 * Math + Prefix XOR.
 * Do the math for what the sequence looks like and what the prefix XOR looks like. You'll notice
 * that the prefix XOR is periodic with period k+1. So we compute the first k+1 terms of the prefix
 * XOR and we can answer queries in O(1).
 * 
 * Time: O(k + q), Mem: O(k)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll k;
vector<ll> v, pref;
int main()
{
    cin >> k;
    v.assign(k + 1, 0);
    pref.assign(k + 1, 0);
    for (int i = 1; i <= k; i++) {
        cin >> v[i];
        pref[i] = pref[i - 1] ^ v[i];
    }

    int q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        l %= (k + 1);
        r %= (k + 1);
        if (l == 0) l = k + 1;
        cout << (pref[r] ^ pref[l - 1]) << endl;
    }

    return 0;
}