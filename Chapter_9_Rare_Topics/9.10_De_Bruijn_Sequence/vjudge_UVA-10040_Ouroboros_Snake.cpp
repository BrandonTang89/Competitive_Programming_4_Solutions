/**vjudge - UVA-10040 - Ouroboros Snake
 * Generate the lexicographically minimal De Bruijn sequence. Base 2 but variable m number of
 * symbols. We just ensure we traverse 0 edges before 1 edges, start at the largest node.
 * 
 * Take note to ensure to take %path.size() when we try to get our reading from the path.
 * Notice that m <= 22 but we can have an "unlimited" number of testcases. As such, we can
 * increase our run time by pre-computing the lexicographically smallest sequence for m in
 * range [1, 22] and processing queries afterwards.
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

int m, u, v, k;

vector<vector<int>> adjlist, path;
void hierholzer(int s) {
    vi idx(v, 0), st;
    st.emplace_back(s);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adjlist[u].size()) {  // still has neighbor
            st.emplace_back(adjlist[u][idx[u]]);
            ++idx[u];
        } else {
            path[m].emplace_back(u&1); // straight away get number in de bruijn sequence
            st.pop_back();
        }
    }
    path[m].pop_back(); // remove initial source vertex
    reverse(path[m].begin(), path[m].end());
}

int main() {
    fast_cin();
    path.assign(22, vi());
    path[0] = {0, 1};
    for (m=1; m<22; m++){
        v = 1 << m;  // 2^m
        adjlist.assign(v, vector<int>(2));
        for (int i = 0; i < v; i++) {
            int q = i & ((v >> 1) - 1);
            q = q << 1;
            adjlist[i][0] = q;
            adjlist[i][1] = q | 1;
        }
        hierholzer(v-1);
    }

    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> m >> k;
        int x = 0;
        for (int i = 0; i < m; i++) {
            x = x << 1;
            x += (path[m-1][(k + i)%(path[m-1].size())]); // circular string
        }
        cout << x << endl;
    }
    return 0;
}