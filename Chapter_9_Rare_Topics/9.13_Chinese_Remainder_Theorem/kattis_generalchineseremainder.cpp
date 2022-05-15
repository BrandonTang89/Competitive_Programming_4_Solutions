/**Kattis - generalchineseremainder
 * Chinese remainder theorem with not necessarily co-prime moduli. We verify validity
 * before we start trying to solve.
 * 
 * Time: O(quite hard to analyse), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll fexp(ll b, ll p){
    if (p == 0)return 1;
	
    ll ans = fexp(b, p >> 1);
    ans = ans * ans;
    if (p & 1) ans = ans * b;
    return ans;
}

ll _sieve_size;
bitset<10000010> bs;
vll primes;

void sieve(ll upperbound = (ll) 1e7){
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for(ll i = 2; i <= _sieve_size; i++){
        if(bs[i]){
            for(ll j = i * i; j <= _sieve_size; j += i){
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    }
}

vector<tuple<ll,ll>> prime_factorise(ll n){
    vector<tuple<ll, ll>> prime_factors;
    int exp;
    for(ll i = 0; i < (ll) primes.size() && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            exp = 0;
            while(n % primes[i] == 0){
                n /= primes[i];
                exp++;
            }
            prime_factors.emplace_back(primes[i], exp);
        }
    }
    if(n != 1){
        prime_factors.emplace_back(n, 1);
    }
    return prime_factors;
}

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

bool verify_crt(vll &r, vll &m) {
    // Ensure r_i = r_j (mod gcd(m_i, m_j)) for all i, j
    for (int i = 0; i < (int)m.size(); ++i) { 
        for (int j = i+1; j < (int)m.size(); ++j) {
            if (mod(r[i], gcd(m[i], m[j])) != mod(r[j], gcd(m[i], m[j]))) {
                return false;
            }
        }
    }
    return true;
}

ll general_crt(vll r, vll m){
    if (!verify_crt(r, m)) {
        return -1;
    }
    unordered_map<ll, ll> prime_highest_pow;
    unordered_map<ll, ll> S;

    for (int i=0; i<(int)m.size(); ++i) {
        vector<tuple<ll, ll>> factors = prime_factorise(m[i]);
        for (int j=0; j<(int)factors.size(); ++j) {
            auto &[p, exp] = factors[j];
            if (prime_highest_pow[p] < exp){
                prime_highest_pow[p] = exp;
                S[p] = r[i] % (fexp(p, exp));
            }
        }
    }

    vll nr, nm;
    for (auto &[p, exp] : prime_highest_pow) {
        // cout << "p = " << p << " exp = " << exp << endl;
        nr.push_back(S[p]);
        nm.push_back(fexp(p, exp));
    }

    return crt(nr, nm);
}
int main(){
    sieve();
    int num_tc;
    ll a, ni, b, mi;
    cin >> num_tc;
    while (num_tc--){
        cin >> a >> ni >> b >> mi;
        vll r = {a, b};
        vll m = {ni, mi};
        
        ll ans = general_crt(r, m);
        if (ans == -1) {
            cout << "no solution\n";
        }
        else{
            cout << ans << " " << lcm(ni, mi) << endl;
        }
    }

    return 0;
}