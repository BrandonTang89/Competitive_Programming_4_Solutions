/* Kattis - primesieve
Simply do the sieve with upperbound of n. Note the following modifications
1. _sieve_size = upperbound instead of upperbound + 1 since we need to to ensure we don't accidentally
   count the number 1 greater than upperbound as a prime.
2. Use a vector of integers rather than long long to store the primes since we know all primes we store
   must be <= 1e8 < 2^31. This prevents MLE.

Time: O(n log log n), Space: O(n)
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll _sieve_size;
bitset<100000010> bs;
vi primes;

// Able to handle 1e7 in < 1s
void sieve(int upperbound){
    _sieve_size = upperbound;
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
    int n, q;
    scanf("%d %d", &n, &q);
    sieve(n);
    printf("%d\n", (int) primes.size());

    int x;
    for (int query=0; query<q; query++){
        scanf("%d", &x);
        printf("%d\n", (int) bs[x]);
    }

    return 0;
}