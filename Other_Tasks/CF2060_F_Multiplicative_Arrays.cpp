#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll n, k;
ll logk;
constexpr ll MOD = 998244353;

int _sieve_size;
constexpr ll inf = 1e18;
vector<ll> lowestpf, primes;
void smallestPF(ll upperbound = (ll) 1e5+2){
    _sieve_size = upperbound + 1;
    lowestpf.assign(_sieve_size, inf);

    for(ll i = 2; i < _sieve_size; i++){
        if(lowestpf[i] == inf){
            lowestpf[i] = i;
            for(ll j = i * i; j < _sieve_size; j += i){
                lowestpf[j] = min(lowestpf[j], i);
            }
            primes.push_back(i);
        }
    }
} // Time: O(n log log n)

constexpr ll mod(ll a, ll n) { return (a % n + n) % n; }
constexpr ll extEuclid(ll a, ll b, ll &x, ll &y) {  // pass x and y by ref
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
constexpr ll modInverse(ll a, ll n = MOD) {  // returns modular inverse of a mod n
    ll x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}


ll memo_comb[50][50];
ll comb(int nn, int r){
    assert(nn >= 0 && r >= 0);
    if (r == 0 || nn == r) return 1;
    if (nn < r) return 0;
    if (memo_comb[nn][r] != -1) return memo_comb[nn][r];
    return memo_comb[nn][r] =  (comb(nn - 1, r - 1) + comb(nn - 1, r)) % MOD;
}

ll stars(int stars, int bins){
    return comb(stars + bins - 1, bins - 1);
}

vector<vector<ll>> f;

int main(){
    smallestPF();
    memset(memo_comb, -1, sizeof memo_comb);
    int tc;
    cin >> tc;
    while(tc--){
        cin >> k >> n;
        logk = 1;
        while ((1LL << logk) <= k) logk++;

        f.assign(k+2, vector<ll>(logk+2, 0));
        for (int x=2; x<=k; x++){
            int p = lowestpf[x];
            int y = x;
            int q = 0;
            while (y % p == 0){
                y /= p;
                q++;
            }

            if (y == 1){
                for (int a=1; a<=logk; a++){
                    f[x][a] = stars(q-a, a);
                }
            }
            else{
                for (int a=1; a<=logk; a++){
                    for (int fresh=0; fresh<a; fresh++){
                        f[x][a] += ((comb(a, fresh) * f[y][a-fresh]) % MOD) * stars(q-fresh, a) % MOD;
                        f[x][a] %= MOD;
                    }
                }
            }
        }

        vector<ll> np1choose(logk+5, 0);
        for (ll a=1; a<np1choose.size(); a++){
            ll num = 1;
            for (int i=0; i<a; i++){
                num = (num * (n+1-i)) % MOD;
            }

            ll den = 1;
            for (int i=1; i<=a; i++){
                den = (den * i) % MOD;
            }

            ll deninv = modInverse(den);
            np1choose[a] = (num * deninv) % MOD;
        }

        cout << n << " "; // 1 is handled separately

        for (int x =2; x<=k; x++){
            ll ans = 0;
            for (int i=1; i<=min(n, logk); i++){
                ans += (f[x][i] * np1choose[i+1]) % MOD;
                ans %= MOD;
            }
            cout << ans << " ";
        }
        cout << endl;
    }


    return 0;
}