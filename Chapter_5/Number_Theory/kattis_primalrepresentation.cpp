/** Kattis - primalrepresentation
 *  
 * Simplish problem involving getting the prime factorisation of numbers
 * 
 * 
 * Time: O(1e7 log log 1e7 + q * pi(sqrt(n))) where pi(sqrt(n) is the number of primes < n
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
/** Computes the prime factorisation of n
 *  Must be run after sieve(), works for n < upperbound_of_sieve**2
 *  
 * @param n the number to factorise
 * @return a vector of tuples of the form (prime, exponent)
 */
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
    sieve();
    ll n;
    while (scanf("%lld", &n) != EOF) {
        auto factors = prime_factorise(abs(n));
        if (n < 0){
            printf("-1 ");
        }
        for (auto &[factor, num] : factors) {
            printf("%lld", factor);
            if (num > 1) {
                printf("^%lld", num);
            }
            printf(" ");
        } 
        printf("\n");
    }

    return 0;
}