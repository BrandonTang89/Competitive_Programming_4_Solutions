/**CF1971H
 * Standard reduction to 2-SAT decision problem solvable via Kosaraju's algorithm
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int num_scc;
const int MAXN = 1002;
vi adjlist[MAXN], adjlist_t[MAXN], scc_index, topo_arr, dfs_num;
vi sccs[MAXN];

void kosaraju(int u, int pass) {
    dfs_num[u] = 1;
    vi &neighbours = (pass == 1) ? adjlist[u] : adjlist_t[u];
    for (auto v : neighbours) {
        if (dfs_num[v] == -1) {
            kosaraju(v, pass);
        }
    }
    if (pass == 1)
        topo_arr.emplace_back(u);
    else {
        scc_index[u] = num_scc;  // colour graph according to num_scc (0 index)
        sccs[num_scc].emplace_back(u); // place the node into the scc
    }
}

int not_vertex(int a){
    if (a < n) return a + n;
    else return a - n;
}

int main() {
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        for (int i=0;i<MAXN;i++){
            adjlist[i].clear();
            adjlist_t[i].clear();
            sccs[i].clear();
        }

        vector<vector<int>> grid(3, vector<int>(n, 0));
        for (int i=0;i<3;i++){
            for (int j=0;j<n;j++){
                cin >> grid[i][j];
                if (grid[i][j] < 0) grid[i][j] = n - grid[i][j] - 1;
                else grid[i][j]--;
            }
        }

        for (int j=0; j<n; j++){
            for (int i=0; i<3; i++){
                for (int k=i+1; k<3; k++){
                    if (i == k) continue;
                    // insert (grid[i][j] or grid[k][j])

                    adjlist[not_vertex(grid[i][j])].emplace_back(grid[k][j]);
                    adjlist[not_vertex(grid[k][j])].emplace_back(grid[i][j]);

                    adjlist_t[grid[k][j]].emplace_back(not_vertex(grid[i][j]));
                    adjlist_t[grid[i][j]].emplace_back(not_vertex(grid[k][j]));
                }
            }
        }


        int N = 2*n; // total number of vertices
        scc_index.assign(N, -1);
        dfs_num.assign(N, -1);
        topo_arr.clear();
        num_scc = 0;

        // Kosaraju First Pass
        for (int i = 0; i < N; i++) {
            if (dfs_num[i] == -1) {
                kosaraju(i, 1);
            }
        }

        // Kosaraju Second Pass, colours the vertices in scc_index
        dfs_num.assign(N, -1);
        for (int i = N - 1; i >= 0; i--) {
            if (dfs_num[topo_arr[i]] == -1) {
                kosaraju(topo_arr[i], 2);
                num_scc++;
            }
        }

        // Check for literal and its negation being in the same SCC
        bool unsat = false;
        for (int i=0;i<n; i++){
            if (scc_index[i] == scc_index[i+n]){ // Xk and not Xk imply each other
                unsat = true;
                break;
            }
        }

        cout << (unsat ? "NO" : "YES") << endl;
    }

}
