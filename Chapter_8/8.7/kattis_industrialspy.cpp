#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define LSOne(S) (S & (-S))
typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size, ans;
bitset<10000010> bs;
vll primes;
vector<int>digits;

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

// Only works for n < sieve_size**2
bool isPrime(ll n){
    if(n < _sieve_size) return bs[n]; // check if n is prime directly for n < sieve_size
    for(ll i = 0; i < (ll) primes.size() && primes[i]*primes[i] <= n; i++){
        // optimised trial division for n < sieve_size**2, 
        if(n % primes[i] == 0){
            return false;
        }
    }
    return true;
}

unordered_set<ll> found;
void search(ll num, int bm){
    if (found.count(num)) return;
    found.insert(num);
    ans += isPrime(num);

    for (int m=bm; m; m-=LSOne(m)){
        int d = digits[__builtin_ctz(m)];
        search(num*10 + d, bm-LSOne(m));
    }
}
int main(){
    sieve();
    int num_tc;
    cin >> num_tc;
    while (num_tc--){
        string s;
        cin >> s;

        digits.clear();
        found.clear();
        for (auto c : s){
            digits.push_back(c - '0');
        }

        int n = digits.size();
        ans = 0;
        search(0, (1 << n) - 1);
        cout << ans << endl;
    }


    return 0;
}