/**CF1848E
 * The idea is to do math to show that for a given x, the number of distinct forces is the number of
 * odd divisors of x.
 *
 * Now, we can precompute the smallest prime factor of each number up to 10^6 using a sieve.
 * This allows us to easily prime factorise any number up to 10^6. Note that we will still need to
 * prime factorise the original x using the standard method of trying all primes less than its
 * square root.
 *
 * We maintain a map xpfactors_map that maps prime factors to their exponents in the prime
 * factorisation of x. Whenever we multiply x by the new number x', we update this map.
 *
 * However, it is too expensive to recompute the product of the exponents for each query. Thus, we
 * maintain a counter of the product and update it via modular multiplication and division. Do note
 * the edge case where z * 0 * 0^(-1) = 0 != z mod M. This means that when we perform a modular
 * inverse of 0, we should recompute the value of the product. Fortunately this is a rare edge case.
 *
 * Time: O(q log 1e6 + sqrt(1e9)), Space: O(1e6)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll x, q, M;
ll _sieve_size;
vector<ll> lowestpf;
vector<ll> primes;

unordered_map<ll, ll> xpfactors_map;

ll mod(ll a, ll n) { return (a % n + n) % n; }

void sieve(ll upperbound = (ll)1e6)
{
    _sieve_size = upperbound + 2;
    lowestpf.assign(_sieve_size, -1);

    for (ll i = 2; i < _sieve_size; i++) {
        if (lowestpf[i] == -1) {
            lowestpf[i] = i;
            for (ll j = i * i; j < _sieve_size; j += i) {
                lowestpf[j] = i;
            }
            primes.push_back(i);
        }
    }
}

ll extEuclid(ll a, ll b, ll &x, ll &y)
{  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
               // ax + by = gcd(a, b)
}

ll modInverse(ll a, ll n)
{  // returns modular inverse of a mod n
    ll x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}

ll ans = 1;
bool recompute = false;

void prime_factorise_sieve(ll n)
{
    assert(n < _sieve_size && n >= 1);
    while (n != 1) {
        ll p = lowestpf[n];
        ll e = 0;
        while (lowestpf[n] == p) {
            n /= p;
            e++;
        }

        if (p == 2) continue;

        ll y = modInverse(xpfactors_map[p] + 1LL, M);
        ans *= y;
        if (y == 0) recompute = true;
        ans %= M;
        ans *= (e + xpfactors_map[p] + 1LL) % M;
        ans %= M;
        xpfactors_map[p] += e;
        xpfactors_map[p] %= M;
    }
}

void prime_factorise(ll n)
{
    int exp;
    for (ll i = 0; i < (int)primes.size() && primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            exp = 0;
            while (n % primes[i] == 0) {
                n /= primes[i];
                exp++;
            }
            xpfactors_map[primes[i]] = exp;
        }
    }
    if (n != 1) {
        xpfactors_map[n] = 1;
    }
}

int main()
{
    cin >> x >> q >> M;
    sieve();
    prime_factorise(x);
    for (auto &[p, e] : xpfactors_map) {
        if (p == 2) continue;
        ans = (ans * (e + 1)) % M;
    }

    while (q--) {
        ll n;
        cin >> n;
        recompute = false;
        prime_factorise_sieve(n);

        if (recompute) {
            ans = 1;
            for (auto &[p, e] : xpfactors_map) {
                if (p == 2) continue;
                ans = (ans * (e + 1)) % M;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
