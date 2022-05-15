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

/** sumDiv returns the sum of all divisors of n.
 * This includes 1 and n.
 * Ensure to run sieve with upperbound**2 > max_n before using this function.
 */
ll sumDiv(ll n){
    ll ans = 1;
    for (int i=0; (i < (int) primes.size() && primes[i] * primes[i] <= n); i++){
        // we attempt tp compute total = (p^0 + p^1 + p^2 + ... + p^k)
        // where k is the number of times primes[i] is in the prime factorisation of n
        ll multiplier = primes[i], total = 1;
        while (n % primes[i] == 0){
            n /= primes[i];
            total += multiplier;
            multiplier *= primes[i];
        }
        ans *= total; // ans = pdt( (p^0 + p^1 + p^2 + ... + p^k) ) for all prime factors
    }
    if (n != 1) ans *= (n + 1) ; // (n^2-1) / (n-1) = n+1
    return ans;
}
int main(){
    sieve(); 
    ll n;
    while (scanf("%lld", &n) != EOF){
        ll ans = sumDiv(n) - n; // since we only consider proper factors here.
        // cout << ans << endl;
        if (ans == n){
            printf("%lld perfect\n", n);
        }
        else if (abs(ans - n) <= 2){
            printf("%lld almost perfect\n", n);
        }
        else{
            printf("%lld not perfect\n", n);
        }
    }



    return 0;
}