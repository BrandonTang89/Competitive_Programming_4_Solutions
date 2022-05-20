/**vjudge - UVA-10506 - The Ouroboros problem
 * Generate any minimal de bruijn sequence for n symbols, length m words. We use the 
 * de bruijn graph with hierholzer algorithm.
 * 
 * Time: O(n^m), Space: O(n^m)
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

int n, m, u, v, e;

// O(log p) exponentiation
ll fexp(ll b, ll p) {
    if (p == 0) return 1;

    ll ans = fexp(b, p >> 1);
    ans = ans * ans;
    if (p & 1) ans = ans * b;
    return ans;
}

vector<vi> adjlist;
vector<int> hierholzer(int s) {
    vi idx(v, 0), st;
    vector<int> ans;
    st.push_back(s);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adjlist[u].size()) {  // still has neighbor
            st.push_back(adjlist[u][idx[u]]);
            ++idx[u];
        } else {
            ans.push_back(u);
            st.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int main() {
    while (cin >> m >> n) {  // number of digits, base
        m--;
        v = fexp(n, m);
        e = v * n;
        adjlist.assign(v, vector<int>());
        for (int i = 0; i < v; i++) {
            int k = i % (v / n);
            k *= n;
            for (int j = 0; j < n; j++) {
                adjlist[i].emplace_back(k + j);
            }
        }
        vector<int> path = hierholzer(0);
        string ans = "";
        for (int i = 0; i < (int)path.size() - 1; i++) {
            ans += to_string(path[i] % n);
        }
        cout << ans << endl;
    }
    return 0;
}