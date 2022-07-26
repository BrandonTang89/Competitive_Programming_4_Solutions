/**Kattis - infinite2darray
 * The first hard question im attempting in a while... First we observe that to get F(x, y), we
 * can sum (F(0, i) * number of ways to get from F(0, i) to F(x, y)) for all i from 0 to y and
 * (F(i, 0) * number of ways to get from F(i, 0) to F(x, y)) for all i from 0 to x. Where number of
 * ways is assuming a path where you from one cell to another by only moving right or down.
 *
 * Now, we observe that F(i, 0) = F(0, i) = Fibo(i) where Fibo(0) = 0, Fibo(1) = 1, Fibo(i) =
 * Fibo(i-1) + Fibo(i-2). We also observe that the number of ways to move from F(a, b) to F(c, d) is
 * (dx + dy C dx) = (dx + dy C dy) where dx = c - a, dy = d - b.
 *
 * It is quite obvious that we should pre-compute Fibo numbers directly. As for nCk values, we can
 * apply Lucas's theorem to compute nCk values quickly. But the usual implementation is too slow. As
 * such, we observe that since 1e9+7 >> 2*1e6, then we can precompute modInverse(fact[i])) for all i
 * in O((x+y) log(1e9)), allowing us to use modInv in O(1) rather than O(log(1e9)).
 *
 * Time: O((x + y) log 1e9), Space: O(x + y)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll MOD = 1e9 + 7;
ll mod(ll a, ll n) { return (a % n + n) % n; }

ll extEuclid(ll a, ll b, ll &x, ll &y) {  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
}

ll modInverse(ll a, ll n) {  // returns modular inverse of a mod n
    ll x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}

vector<ll> modInvfact;
vector<ll> fact;  // facts[p][i] = i! (mod p)
vector<ll> fibo;

ll C(ll n, ll k) {  // lucas theorem, prime modulus index
    return (((fact[n] * modInvfact[k]) % MOD) * modInvfact[n - k]) % MOD;
}
ll x, y;
int main() {
    cin >> x >> y;
    if (y < x) swap(x, y);

    fact.resize(x + y + 1);
    fact[0] = 1;
    for (ll i = 1; i <= x + y; i++) fact[i] = (fact[i - 1] * i) % MOD;

    modInvfact.resize(x + y + 1);
    for (ll i = 0; i <= x + y; i++) modInvfact[i] = modInverse(fact[i], MOD);

    fibo.resize(y + 2);
    fibo[0] = 0;
    fibo[1] = 1;
    for (ll i = 2; i <= y; i++) fibo[i] = (fibo[i - 1] + fibo[i - 2]) % MOD;

    ll ans = 0;
    for (ll i = 1; i <= x; i++) {
        ans += (fibo[i] * C(y - 1 + (x - i), y - 1)) % MOD;
        ans %= MOD;
    }
    for (ll i = 1; i <= y; i++) {
        ans += (fibo[i] * C(x - 1 + (y - i), x - 1)) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}