/**Kattis - magical3
 * Relatively simple: first we observe that we are trying to find the smallest b >= 4 such that
 * n % b == 3. Then we observe that this means that n - 3 = qb for some q. So we compute the
 * divisors of qb. If we have a divisor >= 4, we can use that as b.
 *
 * We also see that for every number >= 7, we will definitely find such a base since we can use
 * n-3 as the base. for n < 7, we always cannot find such a b, except for n == 3.
 * 
 * Time: O(sqrt(n) log n), Mem: O(sqrt(n))
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
    while (true) {
        ll n;
        cin >> n;
        if (n == 0) break;
        if (n == 3) {
            cout << 4 << endl;
        }
        else if (n < 7) {
            cout << "No such base" << endl;
        }
        else {
            vector<ll> factors = getfactors(n - 3);
            sort(factors.begin(), factors.end());
            for (ll factor : factors) {
                if (factor >= 4) {
                    cout << factor << endl;
                    break;
                }
            }
        }
    }

    return 0;
}