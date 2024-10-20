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

template <typename T = ll>
struct StaticSum {
    const int n;
    vector<T> pfs;  // arr[i] contains the range sum from 0 to i inclusively

    T rsq(int l, int r) const {              // range sum from l to r inclusively
        if (l < 0 || r >= n) assert(false);  // boundary condition check
        if (l == 0) return pfs[r];
        return (pfs[r] - pfs[l - 1]);
    }

    StaticSum(const vector<T>& arr) : n(arr.size()), pfs(arr) {
        for (int i = 1; i < n; i++) {
            pfs[i] += pfs[i - 1];
        }
    }
};

vector<vector<pair<int, ll>>> adjlist;
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        adjlist.assign(n, vector<pair<int, ll>>());

        vector<ll> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            v--;
            adjlist[i].push_back({v, arr[i]});
            if (i > 0) {
                adjlist[i].push_back({i - 1, 0});
            }
        }

        // Dijsktra
        const ll inf = 1e15;
        vector<ll> dist(n, inf);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({0, 0});
        dist[0] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : adjlist[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        StaticSum<ll> ss(arr);
        ll best = 0;
        for (int i = 0; i < n; i++) {
            best = max(best, ss.rsq(0, i) - dist[i]);
        }

        cout << best << endl;
    }

    return 0;
}