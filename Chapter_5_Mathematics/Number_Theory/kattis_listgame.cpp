/**Kattis - listgame
 * As simple as counting the number of prime factors of n.
 * 
 * Time: O(number of primes <= sqrt(n)), Mem: O(1)
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
void sieve(ll upperbound = (ll)1e5)
{
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++) {
        if (bs[i]) {
            for (ll j = i * i; j <= _sieve_size; j += i) {
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    }
}

ll prime_factorise(ll n)
{
    ll numPrimeFactors = 0;
    int exp;
    for (ll i = 0; i < (int)primes.size() && primes[i] * primes[i] <= n; i++) {
        if (n % primes[i] == 0) {
            exp = 0;
            while (n % primes[i] == 0) {
                n /= primes[i];
                exp++;
            }
            numPrimeFactors += exp;
        }
    }
    if (n != 1) {
        numPrimeFactors++;
    }
    return numPrimeFactors;
}

int main()
{
    sieve();
    ll n;
    cin >> n;
    cout << prime_factorise(n) << endl;

    return 0;
}