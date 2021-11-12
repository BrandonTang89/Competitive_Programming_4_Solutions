#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size, cross_counter = 0, n, k;
bitset<10000010> bs;
vll primes;

// Able to handle 1e7 in < 1s
void sieve(ll upperbound){
    _sieve_size = upperbound;
    bs.set();
    bs[0] = bs[1] = 0;
    for(ll i = 2; i <= _sieve_size; i++){
        if(bs[i]){
            cross_counter++;
            if (cross_counter == k){
                cout << i << endl;
                return;
            }
            for(ll j = i * i; j <= _sieve_size; j += i){
                if (bs[j] == 1){
                    bs[j] = 0;
                    cross_counter++;
                    if (cross_counter == k){
                        cout << j << endl;
                        return;
                    }
                }
            }
            primes.push_back(i);
        }
    }
}
int main(){
    cin >> n >> k;
    sieve(n);

    return 0;
}