#include <bits/stdc++.h>
using namespace std;

// O(log p) exponentiation with modulus
long long fexp_mod(long long b, long long p, long long mod){
    if (p == 0)return 1;
    if (p == 1)return b;

    if (p & 1){
        return (((fexp_mod(b, p>>1, mod)*fexp_mod(b, p>>1, mod))%mod)*b)%mod;
    }
    else{
        return (fexp_mod(b, p>>1, mod)*fexp_mod(b, p>>1, mod))%mod;
    }   
}

// O(log p) exponentiation without modulus
long long fexp(long long b, long long p){
    if (p == 0)return 1;
    if (p == 1)return b;

    if (p & 1){
        return fexp(b, p>>1)*fexp(b, p>>1)*b;
    }
    else{
        return fexp(b, p>>1)*fexp(b, p>>1);
    }
}