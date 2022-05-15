/**Kattis - stringmatching
 * While this can be solved with KMP (but not suffix array i think, might be too slow), we opt
 * to use Rabin Karp to build a proper implementation of the algorithm.
 * 
 * Time: O(n + m), Space: O(n)
 */ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

string P, T;  // pattern text

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

/**Returns a vector of indices of all occurrences of pattern P in text T.
 * P refers to the pattern, 
 * T refers to the Text hash_params refer to a vector of (p, M) where p and M are used to compute the
 * hash 
 * -> Use more hash parameters to reduce the probability of collisions
 * M should be a large prime, p should be a small prime > number of distinct characters
 */
vi rabinKarp(string P, string T, vector<pair<int, int>> hash_params = {{131, (int)1e9 + 7}}) {
    vector<RollingHash> P_hashes, T_hashes;
    for (int i = 0; i < (int)hash_params.size(); i++) {
        P_hashes.push_back(RollingHash(P, hash_params[i].first, hash_params[i].second));
        T_hashes.push_back(RollingHash(T, hash_params[i].first, hash_params[i].second));
    }
    vi matches;

    int n = T.size(), m = P.size();
    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < (int)hash_params.size(); j++) {
            if (P_hashes[j].getHash(0, m - 1) != T_hashes[j].getHash(i, i + m - 1)) {
                match = false;
                break;
            }
        }
        if (match) matches.push_back(i);
    }
    return matches;
};

int main() {
    fast_cin();
    while (getline(cin, P)) {
        getline(cin, T);
        // cout << P << endl;
        // cout << T << endl;
        vi ans = rabinKarp(P, T, {{131, 1000000007}, {257, 1000000009}, {997, 1000000007}});
        for (int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}