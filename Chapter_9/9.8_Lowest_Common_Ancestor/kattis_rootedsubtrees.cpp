/**Kattis - rootedsubtrees
 * Annoying question. Do some math + logic to figure out a formula for the answer given
 * d, the number of nodes on the path between p and r (inclusive). Do LCA + APSP. 
 * 
 * Time: O(n log n + q), Space: O(< n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, q, idx;
vector<int> adjlist[(int)2e5 + 9];
vector<int> L, E,
    H;  // depth at traversal index, node at traversal index, first traversal index of node

void dfs(int cur, int depth) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    for (int &nxt : adjlist[cur]) {
        if (H[nxt] != -1) continue;
        dfs(nxt, depth + 1);
        E[idx] = cur;  // backtrack to current node
        L[idx++] = depth;
    }
}

class SparseTable {  // OOP style
   private:
    vi A, P2, L2;
    vector<vi> SpT;  // the Sparse Table
   public:
    SparseTable() {}  // default constructor

    SparseTable(vi &initialA) {  // pre-processing routine
        A = initialA;
        int n = (int)A.size();
        int L2_n = (int)log2(n) + 1;
        P2.assign(L2_n + 1, 0);
        L2.assign((1 << L2_n) + 1, 0);
        for (int i = 0; i <= L2_n; ++i) {
            P2[i] = (1 << i);  // to speed up 2^i
            L2[(1 << i)] = i;  // to speed up log_2(i)
        }
        for (int i = 2; i < P2[L2_n]; ++i)
            if (L2[i] == 0) L2[i] = L2[i - 1];  // to fill in the blanks

        // the initialization phase
        SpT = vector<vi>(L2[n] + 1, vi());
        SpT[0] = vi(n, 0);
        for (int j = 0; j < n; ++j) SpT[0][j] = j;  // RMQ of sub array [j..j]

        // the two nested loops below have overall time complexity = O(n log n)
        for (int i = 1; P2[i] <= n; ++i) {             // for all i s.t. 2^i <= n
            SpT[i] = vi(n + 1 - P2[i]);                // initialize SpT[i]
            for (int j = 0; j + P2[i] - 1 < n; ++j) {  // for all valid j
                int x = SpT[i - 1][j];                 // [j..j+2^(i-1)-1]
                int y = SpT[i - 1][j + P2[i - 1]];     // [j+2^(i-1)..j+2^i-1]
                SpT[i][j] = A[x] <= A[y] ? x : y;
            }
        }
    }

    int RMQ(int i, int j) {
        int k = L2[j - i + 1];          // 2^k <= (j-i+1)
        int x = SpT[k][i];              // covers [i..i+2^k-1]
        int y = SpT[k][j - P2[k] + 1];  // covers [j-2^k+1..j]
        return A[x] <= A[y] ? x : y;
    }
};

int LCA(int u, int v, SparseTable &SpT) {
    if (H[u] > H[v]) swap(u, v);
    return E[SpT.RMQ(H[u], H[v])];
}

int APSP(int u, int v, SparseTable &SpT) {
    int ancestor = LCA(u, v, SpT);
    return L[H[u]] + L[H[v]] - 2 * L[H[ancestor]];
}

int main() {
    fast_cin();
    cin >> n >> q;

    L.assign(2 * (n), 0);
    E.assign(2 * (n), 0);
    H.assign(n, -1);
    idx = 0;

    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }
    /*
stack<tuple<int, int, bool>> st; // cur, depth, first_time
st.push ({0, 0, 1});
while (!st.empty()) {
    auto [cur, depth, first_time] = st.top();
    st.pop();

    if (first_time){
        H[cur] = idx;
    }
    E[idx] = cur;
    L[idx++] = depth;
    for (int &nxt : adjlist[cur]) {
        if (H[nxt] != -1) continue;
        st.push({cur, depth, 0});
        st.push({nxt, depth+1, 1});
        break;
    }
    };*/
    dfs(n - 1, 0);
    // cout << idx << endl;
    SparseTable SpT(L);

    ll d;
    while (q--) {
        cin >> u >> v;
        u--;
        v--;
        d = (ll)APSP(u, v, SpT) + 1LL;
        cout << (ll)n - d + (d) * (d + 1) / (ll)2 << endl;
    }

    return 0;
}