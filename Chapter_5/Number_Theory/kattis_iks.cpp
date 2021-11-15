/**Kattis - iks
 * Observe that the operation essentially moves a prime factor from A to B. So actually this problem
 * is about distributing the prime factors as evenly and cheaply as possible such that the score
 * which is the GCD of all the numbers (or the product of all the prime factors the numbers
 * have in common) is maximized.
 * 
 * So the first part is just getting the prime factors of each number and the total number of each
 * prime factor for all the numbers. We store these in a vector of maps and a map respectively.
 * 
 * Then, we iterate through the map and for each prime factor p^e, we split the e factors of p amongst
 * the n numbers, ie each has e/n of p. We then iterate over each number in the sequence and then see
 * if it has less than e/n of p, if so, we use amount_per_num - num[prime] ops to bring it up to e/n.
 * 
 * Similar a the money splitting question a while back, we don't need to deal with number with more than
 * e factors of p since they will "automatically" lose the relevant number of p's without going below
 * e/n.
 * 
 * Time: O(num_distinct_prime_factors * n), Space:(num_distinct_prime_factors * n)
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

map<ll, ll> all_prime_factors;
map<ll, ll> prime_factorise(ll n){
    map<ll, ll> prime_factors; // prime_factor[p] = exp
    int exp;
    for(ll i = 0; i < (int) primes.size() && primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            exp = 0;
            while(n % primes[i] == 0){
                n /= primes[i];
                exp++;
            }
            all_prime_factors[primes[i]] += exp;
            prime_factors[primes[i]] =  exp;
        }
    }
    if(n != 1){
        all_prime_factors[n] += 1;
        prime_factors[n] = 1;
    }
    return prime_factors;
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

int main(){
    int n, a;
    sieve(sqrt(1e6) + 10);
    vector<map<ll, ll>> sequence;
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        scanf("%d", &a);
        sequence.push_back(prime_factorise(a));
    }
    int ops = 0, score = 1;
    for (auto &[prime, exp]: all_prime_factors){
        // printf("%lld^%lld ", prime, exp);
        int amount_per_num = exp / n;
        score *= fexp(prime, amount_per_num);

        for (auto num: sequence){
            if (num[prime] < amount_per_num){
                ops += amount_per_num - num[prime]; // move a prime to this number
            }
        }
    }
    printf("%d %d\n", score, ops);


    return 0;
}