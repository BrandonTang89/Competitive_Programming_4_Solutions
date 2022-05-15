/* Kattis - enlarginghashtables
This is a somewhat introductory problem where we find the smallest prime larger than 2n and check
the primality of n. We use the sieve of eratosthenes and the optimised trial division algorithm.

Note that for for all primes smaller than 3842610773 ( > 2n), the prime gap is always < 319. Thus making
the strategy of just testing each number above 2n for primality sufficiently fast.
Time: O(prime_gap * sqrt(2n))
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

void sieve(ll upperbound){
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

bool isPrime(ll n){
    if(n < _sieve_size) return bs[n]; // check if n is prime directly for n < sieve_size
    for(ll i = 0; i < (ll) primes.size() && primes[i]*primes[i] <= n; i++){
        // optimised trial division for n < sieve_size**2
        if(n % primes[i] == 0){
            return false;
        }
    }
    return true;
}

int main(){
    ll n;
    sieve(1000000);
    while (true){
        scanf("%lld", &n);
        if (n == 0)break;
        ll two_n = n * 2;
        
        for (ll i=two_n + 1; ; i++){
            if (isPrime(i)){
                printf("%lld ", i);
                break; 
            }
        }

        if (!isPrime(n)){
            printf("(%lld is not prime)\n", n);
        }
        else{
            printf("\n");
        }

    }



    return 0;
}