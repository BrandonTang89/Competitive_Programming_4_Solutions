/**Kattis - cocoacoalition
 * Easy after a non-trivial observation.
 *
 * First observe that we can always do 3 cuts or better by setting a = h*(a//w) + (a%w) in 3 cuts.
 * (greedy strategy).
 *
 * Now, we can determine if 1 cut is all we need easily: either a is a multiple of h or w.
 *
 * For 2 cuts, observe that either a or h*w-a must be 1 piece. So if we can express a or h*w-a
 * as p*q where p <= h and q <= w, then we can do 2 cuts. Else 2 cuts is impossible.
 * 
 * So we check for 1 cut, 2 cuts, else 3 cuts.
 * Time: O(sqrt(a)), Mem: O(sqrt(a))
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll h, w, a, b;
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

bool twoCut(ll n)
{
    vector<ll> factors = getfactors(n);
    for (ll factor : factors) {
        if (factor <= h && n / factor <= w) {
            return true;
        }
        if (factor <= w && n / factor <= h) {
            return true;
        }
    }
    return false;
}
int main()
{
    cin >> h >> w >> a;
    b = h * w - a;

    // Try 1 cut
    if (a % h == 0 || a % w == 0) {
        cout << 1 << endl;
        return 0;
    }

    // Try 2 cuts
    if (twoCut(a) || twoCut(b)) {
        cout << 2 << endl;
        return 0;
    }

    // else 3 cuts
    cout << 3 << endl;
    return 0;
}