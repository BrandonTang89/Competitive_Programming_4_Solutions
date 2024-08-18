#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

typedef long long ll;
typedef vector<ll> vll;

constexpr ll inf = 1e18;
vector<ll> lowestpf, primes;
void smallestPF(ll upperbound = (ll) 1e7+2){
    _sieve_size = upperbound + 1;
    lowestpf.assign(_sieve_size, inf);

    for(ll i = 2; i < _sieve_size; i++){
        if(lowestpf[i] == inf){
            lowestpf[i] = i;
            for(ll j = i * i; j < _sieve_size; j += i){
                lowestpf[j] = min(lowestpf[j], i);
            }
            primes.push_back(i);
        }
    }
} // Time: O(n log log n)

unordered_map<ll, ll> primeOrder;

int g(int x){
    if (x == 0) return 0;
    if (x == 1) return 1;
    int pf = lowestpf[x];
    if (pf == 2) return 0;
    return primeOrder[pf];
}

int main(){
    fast_cin();
    smallestPF();
    for (int i = 0; i < primes.size(); i++){
        primeOrder[primes[i]] = i+1;
    }
    
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            ans ^= g(x);
        }

        if (ans == 0){
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    }
    return 0;
}