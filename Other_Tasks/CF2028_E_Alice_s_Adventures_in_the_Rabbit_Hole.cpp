#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

constexpr ll MOD = 998244353;
int n;
vector<vector<int>> adjlist;
vector<int> visited;
vector<int> parent;
vector<ll> depth;

constexpr ll mod(ll a, ll n) { return (a % n + n) % n; }
constexpr ll extEuclid(ll a, ll b, ll &x, ll &y) {  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
               // ax + by = gcd(a, b)
}
constexpr ll modInverse(ll a, ll n) {  // returns modular inverse of a mod n
    ll x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}

void labelDfs(int u) {
    visited[u] = 1;
    for (int v : adjlist[u]) {
        if (visited[v] == 0) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            labelDfs(v);
        }
    }
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        adjlist.assign(n, vector<int>());

        visited.assign(n, 0);
        parent.assign(n, -1);
        depth.assign(n, 0);

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        // root at 0
        depth[0] = 0;
        labelDfs(0);

        vector<pair<int, int>> leaves;  // (depth, node)
        for (int i = 1; i < n; i++) {
            if (adjlist[i].size() == 1) {
                leaves.push_back({depth[i], i});
            }
        }

        sort(leaves.begin(), leaves.end());  // shallowest leaves first

        vector<ll> num(n, -1);  // numerator of the probablity
        vector<ll> den(n, 0);   // denominator of the probability

        num[0] = 1;
        den[0] = 1;

        for (auto [d, leaf] : leaves) {
            int u = leaf;
            int chainLength = 0;  // counts leaf until first finished node (not including finished node)
            while (num[u] == -1) {
                u = parent[u];
                chainLength++;
            }
            ll numFactor = num[u];
            ll denFactor = den[u];

            u = leaf;
            int idx = 0;
            while (num[u] == -1) {
                num[u] = (numFactor * idx) % MOD;
                den[u] = (denFactor * chainLength) % MOD;
                u = parent[u];
                idx++;
            }
        }

        for (int i = 0; i < n; i++) {
            cout << (num[i] * modInverse(den[i], MOD)) % MOD << " ";
        }
        cout << endl;
    }

    return 0;
}