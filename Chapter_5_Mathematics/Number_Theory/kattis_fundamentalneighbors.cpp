/**Kattis - fundamentalneighbors
 * A relatively simple problem if we just modify some of the template code we have written.
 * Just modify the prime factorisation function to return the neighbour of the number, use 
 * fast exponentiation since the exponents we calculate might be large.
 * 
 * Time: O(q * sqrt(n) / log(sqrt(n))), Space: O(1)
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

ll fexp(ll b, ll p){
    if (p == 0)return 1;
    if (p == 1)return b;

    if (p & 1){
        return fexp(b, p>>1)*fexp(b, p>>1)*b;
    }
    else{
        return fexp(b, p>>1)*fexp(b, p>>1);
    }
}


ll neighbour(ll n){
    int exp;
    ll ans = 1;
    for(ll i = 0; i < (int) primes.size() && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            exp = 0;
            while(n % primes[i] == 0){
                n /= primes[i];
                exp++;
            }
            ans *= fexp(exp, primes[i]);
        }
    }
    return ans;
}


int main(){
    ll n;
    vector<tuple<ll,ll>> PF;
    sieve((ll) sqrt(INT_MAX) + 2);
    while (scanf("%lld", &n) != EOF){
        printf("%lld %lld\n", n, neighbour(n));
    }

    return 0;
}