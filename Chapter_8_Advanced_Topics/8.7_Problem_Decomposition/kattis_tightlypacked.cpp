/**Kattis - tightlypacked
 * There might be a big brain way to do this, but complete search is barely fast enough...
 * 
 * Time: O(sqrt(n)), Space: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int main(){
    ll n;
    cin >> n;
    ll best = 1e18;
    for (ll i = 1; i <= sqrt(n); i++) {
        ll h =(n - 1) / i + 1;
        if (h > 2*i) continue;
        best = min(best, (h * i) - n);
    }
    cout << best << endl;

    return 0;
}