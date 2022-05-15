/* Kattis - pascal

The function given stops at the largest divisor of n. This is n/i where i is the smallest prime
factor of n. So after doing sieve, we just find the first prime factor of n (<= sqrt n).

If we still cannot find such a factor. N is prime, so we ouput n-1. Else if n == 1, just output 0.

Time: O(1e6 log log(1e6) + pi(sqrt(n)))
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<10000010> bs;
vll primes;

// Able to handle 1e7 in < 1s
void sieve(ll upperbound = (ll) 1e6){ // 1e6 ** 2 > max_n
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

int main(){
    sieve();
    ll n;
    cin >> n;
    if (n == 1){
        cout << "0" << endl;
        return 0;
    }

    for (auto i: primes){
        if (i > sqrt(n))break;
        if (n % i == 0){
            cout << n - n/i << endl;
            return 0;
        }
    }

    cout << n - 1 << endl;

    return 0;
}