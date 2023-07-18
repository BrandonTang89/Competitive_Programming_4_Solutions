/**Kattis - cpu
 * Math + Pre-computation. We first notice that explosive numbers are actually quite rare. This
 * gives the idea of precomputing all explosive numbers within the required range.
 *
 * We observe that the minimum number x that can be explosive given that a prime p is the smallest
 * prime factor (p1) is roughly O(p^3) since x <= p * (p-1) * (p-2) if A = 1 and B = p-1. This means
 * that since x <= 2e9, we only really need to consider primes <= k * cbrt(2e9) for some k > 1.
 *
 * To ensure we don't miss any, we just consider primes up to sqrt(2e9) == 44721 <= 1e5. There are
 * about 10000 such primes, allowing for the roughly O(n^2) checking of every pair of these as the
 * first 2 primes in an explosive prime to be able to be done during runtime. We observe that each
 * "chain" of explosive primes that comes from expanding the first 2 primes with the formula in
 * the question is relatively "short", i.e. < log 2e9 since we always multiply by at least the
 * first prime. Furthermore, in most of the cases, the chain is actually much shorter than that
 * since the next prime in the chain may not be a prime. All this means that this doesn't TLE.
 *
 * For the queries, we realise that there are only 243 explosive numbers so a linear search is good
 * enough
 * Time: O(1 + q), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

int nprimes1e5 = 0;
ll _sieve_size;
bitset<10000010> bs;
vll primes;

// Able to handle 1e7 in < 1s
void sieve(ll upperbound = (ll)1e7)
{
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++) {
        if (bs[i]) {
            for (ll j = i * i; j <= _sieve_size; j += i) {
                bs[j] = 0;
            }
            primes.push_back(i);
            if (i < 1e5) nprimes1e5++;
        }
    }
}

// Only works for n < sieve_size**2
bool isPrime(ll n)
{
    if (n < _sieve_size) return bs[n];  // check if n is prime directly for n < sieve_size
    for (ll i = 0; i < (ll)primes.size() && primes[i] * primes[i] <= n; i++) {
        // optimised trial division for n < sieve_size**2,
        if (n % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<int> explosives;
    sieve();
    // cout << "nprimes1e5 = " << nprimes1e5 << endl; // 9592

    for (int i = 0; i < nprimes1e5; i++) {
        for (int j = i + 1; j < nprimes1e5; j++) {
            if ((primes[j] - primes[i]) % (primes[i] - 1) == 0) {
                int a = (primes[j] - primes[i]) / (primes[i] - 1);
                int b = primes[i] - a;
                assert(a >= 1);
                ll x = primes[i] * primes[j];
                ll pi = primes[j];

                while (1) {
                    ll pnext = pi * a + b;
                    if (pnext <= 1 || !isPrime(pnext) || (x % pnext == 0)) break;
                    x *= pnext;
                    pi = pnext;
                    if (x > 2e9) break;
                    explosives.push_back(x);
                }
            }
        }
    }

    sort(explosives.begin(), explosives.end());
    // cout << explosives.size() << endl;
    // for (int i=0; i< (int) explosives.size(); i++){
    //     cout << explosives[i] << endl;
    // }

    int tc;
    cin >> tc;
    while (tc--) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int i = 0; i < (int)explosives.size(); i++) {
            if (explosives[i] >= l && explosives[i] <= r) {
                ans++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}