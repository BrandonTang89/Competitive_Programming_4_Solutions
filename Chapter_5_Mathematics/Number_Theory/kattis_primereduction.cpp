/** Kattis - primereduction
 *  
 * Just follow the instructions, use the sieve and the prime factorization algorithms we have
 * developed thus far.
 * 
 * Time: O(1e7 log log 1e7) since the sieve is the main time limiting factor
 * Space: O(1e7)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

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

vector<tuple<ll,ll>> prime_factorise(ll n){
    vector<tuple<ll, ll>> prime_factors;
    int exp;
    for(ll i = 0; i < (int) primes.size() && primes[i] * primes[i] <= n; i++){
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

int main(){
    ll n;
    vector<tuple<ll,ll>> prime_factors;
    sieve();
    while (true){
        scanf("%lld", &n);
        if (n == 4)return 0;

        prime_factors = prime_factorise(n);
        ll counter = 1;
        while (true){
            if (prime_factors.size() == 1){
                auto &[p, e] = prime_factors[0];
                if (p == n){
                    break;
                }
            }
            // printf("n: %lld ", n);
            n = 0;
            for (auto &[p, e] : prime_factors){
                n += p*e;
            }
            prime_factors = prime_factorise(n);
            counter++;
        }

        printf("%lld %lld\n", n, counter);

    }

    return 0;
}