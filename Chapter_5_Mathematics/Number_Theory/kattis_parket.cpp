/**Kattis - parket
 * We get all the divisors of red + brown = total area of room. Then we check if the length and
 * width fit the red and brown area requirements.
 * 
 * Time: O(sqrt(r + b)), Space: O(sqrt(r + b))
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

vector<ll> getfactors(ll n)
{
    vector<ll> factors;
    for (ll i = 1; i <= (int)sqrt(n); i++) {
        if (n % i == 0) {  // i is a factor and n/i is a factor
            factors.emplace_back(i);
            factors.emplace_back(n / i);
        }
    }

    if (floor(sqrt(n)) * floor(sqrt(n)) == n) {  // n is a perfect square
        factors.pop_back();
    }
    return factors;
}
int main()
{
    ll r, b;
    cin >> r >> b;
    ll n = r + b;

    vector<ll> factors = getfactors(n);
    sort(factors.begin(), factors.end());
    for (auto w : factors) {
        ll l = n / w;
        if (2 * (w + l - 2) == r) {
            cout << l << " " << w << endl;
            break;
        }
    }

    return 0;
}