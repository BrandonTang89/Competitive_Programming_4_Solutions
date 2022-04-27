/**Kattis - classicalcounting
 * A distribution problem involving the priciple of inclusion and exclusion. To compute the
 * answer quickly, we make use of Lucas's theorem. Since 1e6 + 7 is not prime but is 
 * square free, we use Lucas's theorem together with chinese remainder theorem.
 * 
 * Time: O(?), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

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

vll MODS = {29, 34483}; // prime factors of a square free modulus
vector<vll> fact; // facts[p][i] = i! (mod p)
ll C(ll n, ll k, ll mod_idx){ // lucas theorem, prime modulus index
    ll MOD = MODS[mod_idx];
    if (n < k) return 0;
    if (n >= MOD)return (C(n % MOD, k % MOD, mod_idx) * C(n / MOD, k / MOD, mod_idx)) % MOD;
    return (((fact[mod_idx][n] * modInverse(fact[mod_idx][k], MOD)) % MOD) * modInverse(fact[mod_idx][n - k], MOD)) % MOD;
}
ll crt(vll &r, vll &m) {
    // m_t = m_0*m_1*...*m_{n-1}
    ll mt = accumulate(m.begin(), m.end(), 1LL, multiplies<>()); // the LL is important!
    ll x = 0;
    for (int i = 0; i < (int)m.size(); ++i) {
        ll a = mod((ll)r[i] * modInverse(mt / m[i], m[i]), m[i]);
        x = mod(x + (ll)a * (mt / m[i]), mt);
    }
    return x;
}

int main(){
    fact.assign(MODS.size(), vll()); // precompute factorials
    for (int i = 0; i < (int) MODS.size(); i++){
        fact[i].push_back(1);
        for (int j = 1; j < MODS[i]; j++){
            fact[i].push_back((fact[i][j - 1] * j) % MODS[i]);
        }
    }

    ll n, k, m;
    cin >> k >> m >> n; // k is then number of bins, n is the number of balls

    vll r;
    for (int j=0; j<(int)MODS.size(); j++){
        ll ans = 0;
        for (ll i=0; (i <= k) && (n >= i*(m+1)); i++){
            ans += (i%2 ? -1 : 1) * C(k, i, j) * C(k-1+n - i*(m+1), k-1, j);
            ans %= MODS[j];
        }
        r.emplace_back(ans);
    }
    cout << crt(r, MODS) << endl;
    return 0;
}