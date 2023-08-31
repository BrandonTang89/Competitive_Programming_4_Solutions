/**Kattis - perfectpowers
 * If n is positive, we just simply prime factorise it then take the GCD of all the exponents.
 * If n is negative, we initially do the same but since p cannot be even, we divide the answer
 * by 2 until it is odd.
 * 
 * Time: O(primes <= sqrt(n)), Mem: O(primes <= sqrt(n))
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

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
        }
    }
}
vector<tuple<ll, ll>> prime_factorise(ll n)
{
    vector<tuple<ll, ll>> prime_factors;
    int exp;
    for (ll i = 0; i < (int)primes.size() && primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            exp = 0;
            while (n % primes[i] == 0) {
                n /= primes[i];
                exp++;
            }
            prime_factors.emplace_back(primes[i], exp);
        }
    }
    if (n != 1) {
        prime_factors.emplace_back(n, 1);
    }
    return prime_factors;
}
int main()
{
    sieve(1e6);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) break;
        bool isNegative = n < 0;
        n = abs(n);

        vector<tuple<ll, ll>> prime_factors = prime_factorise(n);
        ll ans = 0;
        for (auto &[prime, exp] : prime_factors) {
            ans = gcd(ans, exp);
        }
        if (isNegative) {
            while (ans % 2 == 0) {
                ans /= 2;
            }
        }
        cout << ans << endl;
    }

    return 0;
}