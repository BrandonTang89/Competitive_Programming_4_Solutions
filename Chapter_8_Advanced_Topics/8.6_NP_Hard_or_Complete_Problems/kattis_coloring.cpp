/**Kattis - coloring
 * Standard question of finding the chromatic number of a graph. We reduce this problem to the
 * minimum clique problem (minimum number of cliques to partition the graph into) by doing the
 * minimum clique problem on the complement graph. We just use the bitmask DP technique, where
 * dp(bm) is the minimum number of cliques to partition bm into. We iterate through all the subsets
 * of the current bitmask and check if it is a clique (pre-processed). If it is, we can consider
 * dp(bm - ss) + 1.
 * 
 * Time: O(3^n) {some combinatorial argument can be made to show this}, Mem: O(2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) (S & (-S))
int n;
vector<vector<int>> adjmat;
unordered_set<int> cliques;

vector<int> memo;
int dp(int bm)
{  // minimum number of cliques to partition bm into
    if (bm == 0) return 0;
    if (memo[bm] != -1) return memo[bm];

    int ans = 1e8;
    for (int ss = bm; ss; ss = (ss - 1) & bm) {  // iterate through the subsets
        if (cliques.find(ss) != cliques.end()) {
            ans = min(ans, 1 + dp(bm - ss));
        }
    }
    return memo[bm] = ans;
}
int main()
{
    cin >> n;
    cin.ignore();
    adjmat.assign(n, vector<int>(n, 1));
    for (int i = 0; i < n; i++) {
        string line, s;
        getline(cin, line);

        stringstream ss(line);
        while (ss >> s) {
            int j = stoi(s);
            adjmat[i][j] = 0;
        }
    }

    for (int i = 1; i < (1 << n); i++) {
        bool isclique = true;
        int bm = i;
        while (bm != 0 && isclique) {
            int u = __builtin_ctz(bm);
            bm -= LSOne(bm);

            int nbm = bm;
            while (nbm != 0 && isclique) {
                int v = __builtin_ctz(nbm);
                nbm -= LSOne(nbm);
                if (adjmat[u][v] == 0) {
                    isclique = false;
                }
            }
        }
        if (isclique) {
            cliques.insert(i);
        }
    }

    memo.assign(1 << n, -1);
    cout << dp((1 << n) - 1) << endl;

    return 0;
}