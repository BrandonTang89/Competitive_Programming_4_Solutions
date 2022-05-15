/**Kattis - divisors
 * We are tasked to compute the number of divisors for nCk
 * Instead of computing nCk and checking the number of divisors, we instead compute the
 * prime factorisation of nCk. 
 * 
 * Note that nCk = (n!/(k!(n-k)!)), 
 * 
 * We use a map pf where pf[i] is the number of times i occurs in the prime factorisation of nCk
 * 
 * so for each integer in the numerator, we find the prime factors and for each prime p, we 
 * increment pf[p]. For each integer in the deonominator, we find the prime factors and for each
 * prime p, we decrement pf[p].
 * 
 * Finally, we iterate over pf and get the product of (pf[i] +1) for all i in pf.
 * 
 * Time: O(n*pi(n) + sieve time) Since each call of prime_factorise is at most pi(n) and we have n calls
 * Space: O(1e7)
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

map<int, int> pf; // pf[i] = exponent of i
void prime_factorise(ll n, bool add_primes){
    int exp;
    for(ll i = 0; i < (int) primes.size() && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            exp = 0;
            while(n % primes[i] == 0){
                n /= primes[i];
                exp++;
            }
            pf[primes[i]] += exp * (add_primes ? 1 : -1);
        }
    }
    if(n != 1){
        pf[n] += add_primes ? 1 : -1;
    }
}

int main(){
    sieve(10000);
    ll n, k;
    while (cin >> n >> k){
        pf.clear();
        for (int i=n-k+1; i <= n; i++){
            prime_factorise(i, true);
        }
        for (int i=1; i<=k; i++){
            prime_factorise(i, false);
        }

        ll ans = 1;
        for (auto it : pf){
            ans *= (it.second + 1);
        }
        cout << ans << endl;
    }


    return 0;
}