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

int n, k;
int e1, e2;

vector<int> colour1, colour2;
vector<vector<int>> adjlist1, adjlist2;
vector<int> isOut1, isOut2;

void dfs(int u, int c, vector<int>& colour, vector<vector<int>>& adjlist) {
    colour[u] = c;
    for (int v : adjlist[u]) {
        if (colour[v] == -1) {
            dfs(v, (c + 1) % k, colour, adjlist);
        }
    }
}

vector<pair<int, int>> countGoing(vector<int>& colour, vector<int>& isOut) {  // returns {in, out} for each colour
    vector<pair<int, int>> going(k, {0, 0});
    for (int i = 0; i < n; i++) {
        if (isOut[i]) {
            going[colour[i]].second++;
        } else {
            going[colour[i]].first++;
        }
    }
    return going;
}

typedef long long ll;
ll mod(ll a, ll n) { return (a % n + n) % n; }
int extEuclid(int a, int b, int& x, int& y) {
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

int modInverse(int b, int m) {
    int x, y;
    int d = extEuclid(b, m, x, y);  // to get b*x + m*y == d
    if (d != 1) return -1;          // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return mod(x, m);
}

template <int maxN = static_cast<int>(4e5), ll p = 131, ll M = static_cast<int>(1e9) + 7>
class RollingHash {
   private:
    vector<ll> P, P_inv;  // P[i] = p^i % M, P_inv[i] = (p^i)^-1 % M

    vector<ll> H;  // H[i] is the hash of prefix length i
    const int n;
    vector<int> T;
    void computeRollingHash() {  // precompute H
        H.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (i != 0) H[i] = H[i - 1];
            H[i] = (H[i] + ((ll)T[i] * P[i]) % M) % M;
        }
    }

    void PrepareP() {  // precompute P and P_inv
        P.assign(n, 0);
        P[0] = 1;
        for (int i = 1; i < n; i++) P[i] = (P[i - 1] * p) % M;

        P_inv.assign(n, 0);
        P_inv[n - 1] = modInverse(P[n - 1], M);
        for (int i = n - 2; i >= 0; i--) P_inv[i] = (P_inv[i + 1] * p) % M;
    }

   public:
    RollingHash(vector<int>& _s) : n(_s.size()), T(_s) {
        PrepareP();
        computeRollingHash();
    }

    ll getHash(int l, int r) {  // get hash of substring [l, r]
        if (l == 0) return H[r];
        ll ans = ((H[r] - H[l - 1]) % M + M) % M;
        ans = ((ll)ans * P_inv[l]) % M;
        return ans;
    }
};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        isOut1.assign(n, 0);
        isOut2.assign(n, 0);

        colour1.assign(n, -1);
        colour2.assign(n, -1);

        adjlist1.assign(n, vector<int>());
        adjlist2.assign(n, vector<int>());

        for (int i = 0; i < n; i++) cin >> isOut1[i];

        cin >> e1;
        for (int i = 0; i < e1; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist1[u].push_back(v);
        }

        for (int i = 0; i < n; i++) cin >> isOut2[i];

        cin >> e2;
        for (int i = 0; i < e2; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist2[u].push_back(v);
        }

        // edge case: if all nodes on one side are in and all nodes on the other side are out, accept
        bool allIn1 = true;
        bool allOut1 = true;
        for (int i = 0; i < n; i++) {
            if (isOut1[i]) {
                allIn1 = false;
            } else {
                allOut1 = false;
            }
        }

        bool allIn2 = true;
        bool allOut2 = true;
        for (int i = 0; i < n; i++) {
            if (isOut2[i]) {
                allIn2 = false;
            } else {
                allOut2 = false;
            }
        }

        if ((allIn1 && allOut2) || (allIn2 && allOut1)) {
            cout << "YES" << endl;
            continue;
        }

        dfs(0, 0, colour1, adjlist1);
        dfs(0, 0, colour2, adjlist2);

        // we count the number of in going and out going edges of each colour in colour1 and colour2

        vector<int> outs1, ins1, outs2, ins2;

        vector<pair<int, int>> going1 = countGoing(colour1, isOut1);
        for (int i = 0; i < k; i++) {
            outs1.push_back(going1[i].second);
            ins1.push_back(going1[i].first);
        }
        for (int i = 0; i < k; i++) {
            outs1.push_back(going1[i].second);
            ins1.push_back(going1[i].first);
        }
        for (int i = 0; i < k; i++) {
            outs1.push_back(going1[i].second);
            ins1.push_back(going1[i].first);
        }

        vector<pair<int, int>> going2 = countGoing(colour2, isOut2);
        for (int i = 0; i < k; i++) {
            outs2.push_back(going2[i].second);
            ins2.push_back(going2[i].first);
        }

        RollingHash<> rhins1(ins1), rhouts1(outs1), rhins2(ins2), rhouts2(outs2);

        ll hashins2 = rhins2.getHash(0, k - 1);
        ll hashouts2 = rhouts2.getHash(0, k - 1);

        bool found = false;
        for (int i = 0; i < k; i++) {
            ll hashouts1 = rhouts1.getHash(i, i + k - 1);
            ll hashins1 = rhins1.getHash(i+2, i + 2 + k - 1);

            if ( hashouts1 == hashins2 && hashins1 == hashouts2) {
                cout << "YES" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "NO" << endl;
        }
    }

    return 0;
}