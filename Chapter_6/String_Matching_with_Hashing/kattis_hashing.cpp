/**Kattis - hashing
 * This is just asking for any hashing. Since we have already developed our rolling hash, we just use
 * it. There is the special contraint that our hash should be a 64 bit non-negative integer. So
 * we can use the trick of setting the first 32 bits as the one hash and the next 32 bits as
 * another hash. See below for implementation.
 * 
 * Time: O(n + q), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll mod(ll a, ll n) { return (a % n + n) % n; }
int extEuclid(int a, int b, int &x, int &y) {  // pass x and y by ref
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

int modInverse(int b, int m) {  // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);  // to get b*x + m*y == d
    if (d != 1) return -1;          // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return mod(x, m);
}

class RollingHash {
   public:
    vi P, H;   // P[i] = p^i mod m, H[i] is the hash of prefix length i
    vi P_inv;  // P_inv[i] = p^(-i) mod m
    const int n;
    string T;
    const ll p, M;

    RollingHash(string _s, int _p = 131, int _M = (int)1e9 + 7)
        : n(_s.size()), T(_s), p(_p), M(_M) {
        PrepareP();
        computeRollingHash();
    }
    void PrepareP() {  // precompute P and P_inv
        P.assign(n, 0);
        P[0] = 1;
        for (int i = 1; i < n; i++) P[i] = (P[i - 1] * p) % M;

        P_inv.assign(n, 0);
        P_inv[n - 1] = modInverse(P[n - 1], M);
        for (int i = n - 2; i >= 0; i--) P_inv[i] = (P_inv[i + 1] * p) % M;
    }

    void computeRollingHash() {  // precompute H
        H.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (i != 0) H[i] = H[i - 1];
            H[i] = (H[i] + ((ll)T[i] * P[i]) % M) % M;
        }
    }

    int getHash(int l, int r) {  // get hash of substring [l, r]
        if (l == 0) return H[r];
        int ans = ((H[r] - H[l - 1]) % M + M) % M;
        ans = ((ll)ans * P_inv[l]) % M;
        return ans;
    }
};

string T;
int num_q, l, r;
int main(){
    cin >> T;
    RollingHash rh1(T);
    RollingHash rh2(T, 313, (int)1e9 + 7);

    cin >> num_q;
    for(int i = 0; i < num_q; i++){
        cin >> l >> r; // [l,r)
        r--;
        ll combined_hash = ((ll) rh1.getHash(l, r) << 32) + (ll) rh2.getHash(l, r);
        cout << combined_hash << endl;
    }

    return 0;
}