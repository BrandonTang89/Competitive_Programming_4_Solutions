/* Kattis - dominos
SCC to DAG compression, count number of DAG nodes with 0 in-degree. This time, we choose to use
kosaraju just to spice things up.

Time: O(V + E), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, t, num_scc;
vi adjlist[100009], adjlist_t[100009], scc_index, topo_arr, dfs_num;
bool scc_non_0_in_deg[100009]; // true if scc has a non zero degree

void kosaraju(int u, int pass){
    dfs_num[u] = 1;
    vi &neighbours = (pass == 1) ? adjlist[u] : adjlist_t[u];
    for (auto v: neighbours){
        if (dfs_num[v] == -1){
            kosaraju(v, pass);
        }
    }
    topo_arr.emplace_back(u);

    //printf("u: %d, pass: %d, num_scc: %d\n", u, pass, num_scc);
    if (pass == 2){
        scc_index[u] = num_scc; // colour graph according to num_scc (0 index)
    }
}

int main(){
    fast_cin();
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> n >> e;
        
        for (int i=0;i<n;i++){
            adjlist[i].clear();
            adjlist_t[i].clear();
        }
        scc_index.assign(n, -1);
        dfs_num.assign(n, -1);
        topo_arr.clear();
        num_scc = 0;
        for(int i=0;i<n;i++)
            scc_non_0_in_deg[i]= false;

        for (int i=0;i<e; i++){
            cin >> u >> v;
            u--; v--;
            adjlist[u].emplace_back(v);
            adjlist_t[v].emplace_back(u);
        }

        for (int i=0;i<n;i++){
            if (dfs_num[i] == -1){
                kosaraju(i, 1);
            }
        }
        // for (auto i: topo_arr){cout << i << " ";} cout << endl;

        dfs_num.assign(n, -1);
        for (int i=n-1; i>=0; i--){
            if (dfs_num[topo_arr[i]] == -1){
                kosaraju(topo_arr[i], 2);
                num_scc++;
            }
        }


        for (u = 0; u<n; u++){
            for (auto v: adjlist[u]){
                if (scc_index[v] == scc_index[u])continue;

                //printf("u: %d, v: %d\n", u, v);
                scc_non_0_in_deg[scc_index[v]] = true;
            }
        }

        //for (int i=0; i<n; i++){cout << scc_index[i] << " ";} cout << endl;
        int ans = 0;
        for (int i=0;i<num_scc;i++){
            if (scc_non_0_in_deg[i] == false)ans++;
        }
        cout << ans << endl;
    }


    return 0;
}