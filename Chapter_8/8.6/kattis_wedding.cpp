// #pragma GCC optimize("Ofast")
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
#define MAX_N 100

int n, m, u, v;
int num_scc;
string s1, s2;
vi adjlist[MAX_N], adjlist_t[MAX_N], scc_index, topo_arr, dfs_num;
unordered_set<int> adjlist_dag[MAX_N];
vi sccs[MAX_N];

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

int parse_guest(string x) {  // converts xxxh and xxxw to xxx and xxx + n
    int num = stoi(x.substr(0, x.size() - 1));
    // zero index
    if (x[x.size() - 1] == 'h')
        return num;
    else
        return num + n;
}

int not_vertex(int a){
    if (a < n) return a + n;
    else return a - n;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> s1 >> s2;
        u = parse_guest(s1);
        v = parse_guest(s2);

        adjlist[not_vertex(u)].push_back(v);
        adjlist[not_vertex(v)].push_back(u);

        adjlist_t[u].push_back(not_vertex(v));
        adjlist_t[v].push_back(not_vertex(u));
    }

    adjlist[0].push_back(not_vertex(0)); // (Not x0 or Not x0) ie x0 must be false because wifey sits on the same
                                         // side as wifey

    int N = 2*n;
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
    for (int i=1;i<n; i++){
        if (scc_index[i] == scc_index[i+n]){
            cout << "bad luck" << endl;
            return 0;
        }
    }

    // Compress SCCs to DAG nodes
    for (u = 0; u < N; u++) {
        for (auto v : adjlist[u]) {
            if (scc_index[v] == scc_index[u]) continue;
            // There exist an edge from (scc_index[u] --> scc_index[v])
            adjlist_dag[scc_index[u]].insert(scc_index[v]);
        }
    }

    // Assign truth values based on Reverse Topological Sort of the DAG
    vi truth_values(n, 0); // 0 for unassigned, 1 for true, 2 for false
    for (int i=num_scc-1; i>=0; i--) {
        for (auto v : sccs[i]) {
            if (v < n) {
                if (truth_values[v] == 0)
                    truth_values[v] = 1;
            } else {
                 if (truth_values[v-n] == 0)
                    truth_values[v-n] = 2;
            }
        }
    }

    for (int i=1; i<n; i++){
        if (truth_values[i] == 1){
            cout << i << "h ";
        }
        else{
            cout << i << "w ";
        }
    }



    return 0;
}