/**Kattis - typo
 * We add a custom method to our rolling hash class, "typoHash", that returns the hash of the string
 * after deleting a single word in O(1) time (due to our precomputed P values).
 * 
 * To solve this problem, we get 2 different hashes of all the words in the dictionary, store in
 * a hash table, then we get the typo hash of all the words in the dictionary, then for each typo,
 * test if its hash exists in the hash table. If it does, we have a typo.
 * 
 * Note that using 2 different hashes is required to reduce the probability of collisions.
 * Time: O(total number of chars), Space: O(total number of chars)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int> &v) const {
        std::size_t seed = 0;
        seed ^= v.first + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= v.second + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

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
    int totalHash;

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
        totalHash = H[n - 1];
    }

    int getHash(int l, int r) {  // get hash of substring [l, r]
        if (l > r) return 0;
        if (l == 0) return H[r];
        int ans = ((H[r] - H[l - 1]) % M + M) % M;
        ans = ((ll)ans * P_inv[l]) % M;
        return ans;
    }

    int typoHash(int i) {  // hash with ith character removed
        return (getHash(0, i - 1) + (((ll)getHash(i + 1, n - 1) * P[i]) % M)) % M;
    }
};

int w;
string T;
vector<RollingHash> V1, V2;
unordered_set<pair<int, int>, pair_hash> us;
int main() {
    cin >> w;
    for (int i = 0; i < w; i++) {
        cin >> T;
        RollingHash r1(T);
        V1.push_back(r1);
        RollingHash r2(T, 313, (int)1e9 + 7);
        V2.push_back(r2);

        // cout << T << endl;
        // cout << r1.totalHash << "-" << r2.totalHash << endl;
        us.insert({r1.totalHash, r2.totalHash});
    }

    bool exist_typos = false;
    for (int i = 0; i < w; i++) {
        bool typo = false;
        for (int j = 0; j < V1[i].n && !typo; j++) {
            // cout << i << " : " << j << endl;
            // cout << V1[i].typoHash(j) << " " << V2[i].typoHash(j) << endl;

            if (us.find({V1[i].typoHash(j), V2[i].typoHash(j)}) !=
                us.end()) {  // typo exist in dictionary
                cout << V1[i].T << endl;
                typo = true;
                exist_typos = true;
                break;
            }
        }
    }

    if (!exist_typos) cout << "NO TYPOS" << endl;

    return 0;
}