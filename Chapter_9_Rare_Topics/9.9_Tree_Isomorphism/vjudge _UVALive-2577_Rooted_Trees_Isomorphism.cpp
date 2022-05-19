/**vjudge - UVALive-2577
 * Note that we cannot submit this solution, but I have tested it on a similar problem (see
 * below). Essentially the idea is that we should hash the tree somehow so we can compare it
 * with another tree. We use a similar hash function as in the rabin karp string matching
 * algorithm but with some modifications to avoid hashing 2 different trees to the same
 * number.
 * 
 * Time: O(n log n) since we could be sorting, Space: O(n)
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

class Hasher {
   public:
    vector<ll> P;   // P[i] = p^i mod m, H[i] is the hash of prefix length i
    vector<ll> P_inv;  // P_inv[i] = p^(-i) mod m
    const int n;
    const ll p, M;

    Hasher(int initN, int _p = 131, int _M = (int)1e9 + 7)
        : n(initN), p(_p), M(_M) {
        PrepareP();
    }
    void PrepareP() {  // precompute P and P_inv
        P.assign(n, 0);
        P[0] = 1;
        for (int i = 1; i < n; i++) P[i] = (P[i - 1] * p) % M;

        P_inv.assign(n, 0);
        P_inv[n - 1] = modInverse(P[n - 1], M);
        for (int i = n - 2; i >= 0; i--) P_inv[i] = (P_inv[i + 1] * p) % M;
    }

    ll hashVector(vector<ll> &V){
        ll cur = p;
        for (int i = 0; i < (int)V.size(); i++) {
            cur = (cur + ((ll)V[i] * P[i]) % M) % M;
        }
        return cur; 
    }
};
vector<vector<int>> children;
vector<int> indegree;

ll encode(int u, Hasher &H){
    if ((int) children[u].size() == 0) return 1; // leaves have value 1
    vector<ll> V;
    V.push_back(1);
    for (int i = 0; i < (int)children[u].size(); i++) {
        V.push_back(encode(children[u][i], H));
    }
    sort(V.begin(), V.end());
    return H.hashVector(V);
}

int k, n, root;
int main(){
    cin >> k >> n;
    Hasher H(n);
    vector<ll> hashes;

    for (int i=0; i<k; i++){
        children.assign(n, vector<int>());
        indegree.assign(n, 0);
        for (int j=0; j<n-1; j++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            children[u].push_back(v);
            indegree[v]++;
        }
        for (int j=0; j<n; j++){
            if (indegree[i] == 0){
                root = i;
                break;
            }
        }
        hashes.emplace_back(encode(root, H));
    }

    vector<bool> done(n, false);
    for (int i=0; i<k; i++){
        if (done[i])continue;
        done[i] = true;
        cout << i+1;
        for (int j=i+1; j<k; j++){
            if (hashes[j] == hashes[i]){
                cout << " = " << j+1;
                done[j] = true;
            }
        }
        cout << " ;" << endl;
    }

    return 0;
}


/* Gets AC on https://csacademy.com/contest/archive/task/binary-isomorphism/statement/
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

class Hasher {
   public:
    vector<ll> P;   // P[i] = p^i mod m, H[i] is the hash of prefix length i
    vector<ll> P_inv;  // P_inv[i] = p^(-i) mod m
    const int n;
    const ll p, M;

    Hasher(int initN, int _p = 131, int _M = (int)1e9 + 7)
        : n(initN), p(_p), M(_M) {
        PrepareP();
    }
    void PrepareP() {  // precompute P and P_inv
        P.assign(n, 0);
        P[0] = 1;
        for (int i = 1; i < n; i++) P[i] = (P[i - 1] * p) % M;

        P_inv.assign(n, 0);
        P_inv[n - 1] = modInverse(P[n - 1], M);
        for (int i = n - 2; i >= 0; i--) P_inv[i] = (P_inv[i + 1] * p) % M;
    }

    ll hashVector(vector<ll> &V){
        ll cur = p;
        for (int i = 0; i < (int)V.size(); i++) {
            cur = (cur + ((ll)V[i] * P[i]) % M) % M;
        }
        return cur; 
    }
};
vector<vector<int>> children;

ll encode(int u, Hasher &H){
    if ((int) children[u].size() == 0) return 1; // leaves have value 1
    vector<ll> V;
    V.push_back(1);
    for (int i = 0; i < (int)children[u].size(); i++) {
        V.push_back(encode(children[u][i], H));
    }
    sort(V.begin(), V.end());
    return H.hashVector(V);
}

int n, root;
int main(){
    Hasher H(1e5 + 9);
    int num_tc;

    cin >> num_tc;
    while(num_tc--){
        cin >> n;
        vector<ll> hashes;
        for (int i=0; i<2; i++){
            children.assign(n, vector<int>());
            for (int j=0; j<n; j++){
                int p;
                cin >> p;
                p--;
                if (p == -1) root = j;
                else children[p].push_back(j);
            }
            hashes.emplace_back(encode(root, H));
        }
        if (hashes[0] == hashes[1]) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}*/