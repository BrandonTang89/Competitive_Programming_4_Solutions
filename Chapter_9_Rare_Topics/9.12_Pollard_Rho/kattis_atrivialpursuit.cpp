/**Kattis - atrivialpursuit
 * Fast factorisation + combinatorics.
 * Let PiG and PiL be the products of G and L respectively. For a given prime pi, we let the
 * exponent in PiG of pi be ai and that in PiL be bi. Notice that amongst all the xj from [1, p], we
 * have that the exponent of pi in xj, kji must be in the range [ai, bi] with at least 1 xj have kji
 * = ai and at least 1 xj have kji = bi. So we can use the principle of inclusion and exclusion to
 * determine the number of ways to set the exponents of pi across all x. Ie number of ways = (bi -
 * ai + 1)^p - (bi - ai)^p - (bi - ai)^p + (bi - ai -1)^p. Which correspond to the ranges [ai, bi],
 * [ai,bi), (ai, bi] and (ai, bi) respectively. Then across all pi, we just multiple the number of
 * ways since they are independent. (Note edge cases where ai=bi, and ai>bi).
 *
 * The real difficult part is how to get the factorisation of PiG and PiL. We can just factorise
 * each Gi and Li by themselves and add it to some container, in our case, a hashmap of prime ->
 * exponent. In fact, since we are only using bi-ai for all i, we can just use 1 container which
 * contains prime -> bi-ai.
 *
 * But even factorising each Gi and Li is difficult as they are in the range of [1,1e18]. To do so,
 * we utilise the Rabin-Miller primality test together with the Pollard Rho's algorithm with brent's
 * modification. Note that without brent's modification, the algorithm will be too slow when factoring
 * large 2 prime composite numbers like 987494726787828293 = 999999937 * 987494789.
 *
 * While the algorithms themselves are not too hard, the problem is the frequency of overflow and
 * the lack of proper support for 128 bit integers. We use the 128 bit integers sparingly, whenever
 * we multiply 2 numbers that are > INT_MAX together. It may be hard to see which lines require the
 * use of 128 bit integers, analyse the code below. Note that we cannot just throw 128 bit integers
 * everywhere because alot of functions like cout, abs, gcd, etc don't suppor them. Assume we can
 * only use the basic +,-,*,/,% operators with them, thus we need to cast to and from __int128
 * often.
 *
 * Time: O(no one really knows), Space: O(idk either)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 int128;

ll p, n, m;
ll MOD = 1e9 + 7;
unordered_map<ll, ll> pi;  // pi[prime] = exp, ie prime^exp is part of the prime factorisation

ll mod(ll a, ll b) { return (a % b + b) % b; }
ll power(int128 x, int128 y, int128 p) {
    int128 res = 1;  // Initialize result
    x = x % p;       // Update x if it is more than or
                     // equal to p
    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1) res = (res * x) % p;

        // y must be even now
        y = y >> 1;  // y = y/2
        x = (x * x) % p;
    }
    return res;
}
bool millerTest(ll d, ll n) {
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    ll a = 2 + rand() % (n - 4);

    // Compute a^d % n
    int128 x = power(a, d, n);

    if (x == 1 || x == n - 1) return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    // Return composite
    return false;
}
bool isPrime(ll n, int k = 4) {
    // Corner cases
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;

    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
        if (!millerTest(d, n)) return false;

    return true;
}
ll Rho(ll n) {
    if (n % 2 == 0) return 2;
    ll x = (rand() % (n - 2)) + 2;
    ll y = x;
    ll c = (rand() % (n - 1)) + 1;

    ll d = 1;
    while (d == 1) {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        x = (power(x, 2, n) + c + n) % n;

        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (power(y, 2, n) + c + n) % n;
        y = (power(y, 2, n) + c + n) % n;

        /* check gcd of |x-y| and n */
        d = __gcd(abs(x - y), n);
        if (d == n) return Rho(n);
    }

    return d;
}
ll brent(ll n) {
    if (n % 2 == 0) return 2;
    ll y = rand() % (n - 1) + 1;
    ll c = rand() % (n - 1) + 1;
    ll m = rand() % (n - 1) + 1;
    ll g = 1, r = 1, q = 1;
    ll ys, x;
    while (g == 1) {
        x = y;
        for (int i = 0; i < r; i++) {
            y = (power(y, 2, n) + c + n) % n;
        }
        ll k = 0;
        while (k < r && g == 1) {
            ys = y;
            for (ll i = 0; i < min(m, r - k); i++) {
                y = (power(y, 2, n) + c + n) % n;
                q = ((int128)q * (int128)(abs((x - y)))) % n;
            }
            g = gcd(q, n);
            k = k + m;
        }
        r = r * 2;
    }
    if (g == n) {
        while (1) {
            ys = (power(ys, 2, n) + c + n) % n;
            g = gcd(abs((x - ys)), n);
            if (g > 1) break;
        }
    }

    return g;
}
void PollardRho(ll n, ll adding) {
    if (n == 1) return;  // # no prime divisor for 1
    if (isPrime(n)) {
        if (pi.find(n) == pi.end()) {
            pi[n] = 0;
        }
        pi[n] += adding;
        return;
    }

    ll d = brent(n);  // try changing to rho (brent is the upgraded version)

    PollardRho(d, adding);
    PollardRho(n / d, adding);
}
int main() {
    srand(time(NULL));

    cin >> p >> n >> m;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        PollardRho(x, -1);
    }
    for (ll i = 1; i <= m; i++) {
        ll x;
        cin >> x;
        PollardRho(x, 1);
    }
    bool impossible = false;
    ll ans = 1;
    for (auto &[prime, exp] : pi) {
        // cout << "prime "  << prime << " exp " << exp << endl;
        if (exp < 0) {
            impossible = true;
            break;
        }
        if (exp == 0) continue;

        ll delta = power(exp + 1, p, MOD);
        delta += power(exp - 1, p, MOD);
        delta %= MOD;
        delta -= ((2 * power(exp, p, MOD)) % MOD);
        delta = mod(delta, MOD);
        delta %= MOD;

        ans *= delta;
        ans %= MOD;
    }
    if (impossible)
        cout << 0 << endl;
    else
        cout << ans << endl;

    return 0;
}