/**Kattis - boxes
 * Simple modification of LCA routine: Make a super node that contains all the boxes, modify the DFS
 * to gather sub-tree size information. For each query, we only add the subtree size of boxes that
 * are the maximal boxes (are not contained in any other boxes) in the query.
 *
 * Time: O(n log n + q (num_q^2)), Space: O(n log n)
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
#define MAX_N 200009

int n, idx;
vector<vector<int>> children;
vector<int> L(2 * MAX_N, 0), E(2 * MAX_N, 0), H(MAX_N, 0), subtree_size(MAX_N, 0);

void dfs(int cur, int depth) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    subtree_size[cur] = 1;
    for (auto &nxt : children[cur]) {
        dfs(nxt, depth + 1);
        E[idx] = cur;  // backtrack to current node
        L[idx++] = depth;
        subtree_size[cur] += subtree_size[nxt];
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
        P2.assign(L2_n, 0);
        L2.assign(1 << L2_n, 0);
        for (int i = 0; i <= L2_n; ++i) {
            P2[i] = (1 << i);  // to speed up 2^i
            L2[(1 << i)] = i;  // to speed up log_2(i)
        }
        for (int i = 2; i < P2[L2_n]; ++i)
            if (L2[i] == 0) L2[i] = L2[i - 1];  // to fill in the blanks

        // the initialization phase
        SpT = vector<vi>(L2[n] + 1, vi(n));
        for (int j = 0; j < n; ++j) SpT[0][j] = j;  // RMQ of sub array [j..j]

        // the two nested loops below have overall time complexity = O(n log n)
        for (int i = 1; P2[i] <= n; ++i)               // for all i s.t. 2^i <= n
            for (int j = 0; j + P2[i] - 1 < n; ++j) {  // for all valid j
                int x = SpT[i - 1][j];                 // [j..j+2^(i-1)-1]
                int y = SpT[i - 1][j + P2[i - 1]];     // [j+2^(i-1)..j+2^i-1]
                SpT[i][j] = A[x] <= A[y] ? x : y;
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

int main() {
    cin >> n;
    n++;
    children.assign(n, vector<int>());

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        children[p].emplace_back(i);
    }
    dfs(0, 0);
    SparseTable SpT(L);

    int q;
    cin >> q;
    while (q--) {
        int num_q;
        cin >> num_q;
        vector<int> v(num_q);
        for (int i = 0; i < num_q; i++) {
            cin >> v[i];
        }
        int ans = 0;
        for (auto i : v) {
            bool biggest = true;
            for (auto j : v) {
                if (i == j) continue;
                if (LCA(i, j, SpT) == j) {
                    biggest = false;
                    break;
                }
            }
            if (biggest) {
                ans += subtree_size[i];
            }
        }
        cout << ans << endl;
    }

    return 0;
}