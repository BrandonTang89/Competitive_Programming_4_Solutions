/**Kattis - disgruntledjudge
 * Straightforward iterative complete search
 * 
 * Time: O(10001^2), Mem: O(10001)
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

ll n;
vector<ll> v;
int main()
{
    fast_cin();
    cin >> n;
    v.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (ll a = 0; a <= 10000; a++) {
        for (ll b = 0; b <= 10000; b++) {
            bool valid = true;
            for (ll i = 1; i < n; i++) {
                if (v[i] != (a * a * v[i - 1] + a * b + b) % 10001LL) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                for (ll i = 0; i < n; i++) {
                    cout << (a * v[i] + b) % 10001LL << endl;
                }
                return 0;
            }
        }
    }
    assert(false);

    return 0;
}