/* Kattis - goldbach2

Determine the number of ways a number can be represented as the sum of 2 primes.
We use the sieve of Eratosthenes as preprocessing. Then for each prime number less than 
or equal to half the number, check if n - p is a prime. If so, we have found a solution.

Time: O(n log log n + qn/ ln(n)), Space: O(n)
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

int q, n;

// Able to handle 1e7 in < 1s
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


int main(){
    sieve(32005);
    
    scanf("%d", &q);
    for(int t=0;t<q;t++){
        scanf("%d", &n);
        vector<pair<int,int>> ans;
        for (int i=0;i<(int)primes.size();i++){
            if (primes[i]>n/2) break;
            if (bs[n-primes[i]]){
                ans.push_back(make_pair(primes[i],n-primes[i]));
            }
        }
        printf("%d has %d representation(s)\n", n, (int)ans.size());
        for (int i=0;i<(int)ans.size();i++){
            printf("%d+%d\n",ans[i].first, ans[i].second);
        }
        printf("\n");
    }
    return 0;
}