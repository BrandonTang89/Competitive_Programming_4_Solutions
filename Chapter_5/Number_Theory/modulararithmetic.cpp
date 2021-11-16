/**Kattis-modulararithmetic
 * Simply do modular arithmetic on the input. Use modInverse when needed.
 * 
 * Time: O(q) assuming that a,b are small enough for the extEuclid to be almost O(1)
 * Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
ll n, t;
ll a, b, ans;
char op;
ll mod(ll a, ll n) { return (a % n + n) % n; }
ll extEuclid(ll a, ll b, ll &x, ll &y) {  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
}

ll modInverse(ll b, ll m) {  // returns b^(-1) (mod m)
    ll x, y;
    ll d = extEuclid(b, m, x, y);  // to get b*x + m*y == d
    if (d != 1) return -1;          // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return mod(x, m);
}

int main(){
    while (true){
        scanf("%lld %lld", &n, &t);
        if (n == 0 && t == 0) break;
        for (int k=0; k<t; k++){
            scanf("%lld %c %lld", &a, &op, &b);
            if (op == '+'){
                ans = mod(a+b, n);
            }
            else if (op == '-'){
                ans = mod(a-b, n);
            }
            else if (op == '*'){
                ans = mod(a*b, n);
            }
            else if (op == '/'){
                ans = modInverse(b, n);
                if (ans != -1) ans = mod(a*ans, n);
            }

            printf("%lld\n", ans);
        }

    }

    return 0;
}