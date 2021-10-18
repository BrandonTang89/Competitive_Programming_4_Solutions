/* Kattis - equivalences
This is a question that requires us to find SCCs and compress them to form a directed acyclic graph.

Observation 1:
    For all the statements to prove each other, at the end, the graph must be strongly connected. That way, any 2 statements
    imply each other directly or indirectly.

Observation 2:
    If we compress all SCCs, we get a DAG which we then need to convert to a strongly connected graph. But what is the minimum
    number of edges we must add to achieve this strongly connected graph?

    Note that in a strongly connected graph, each vertex has a non-zero in and out degree. This is because if it had 0 in-degree,
    then nothing would be able to travel to it (similar argument for out degree). However, just because all vertices have non-zero
    in and out degrees doesn't gaurantee it to be strongly connected.

    It turns out, that the best way to construct this strongly connected graph is to connect all 0 out degree vertices with another 0 in
    degree vertex. This way, we are slowly "piecing together a big cycle". From the above, we already know this is minimal since all
    vertices have to have non-zero in and out degree anyway. If there are more vertices with out degree 0 than vertices with in degree
    0, then we can just add edges from those vertices to anywhere along the "big cycle" that we have already constructed.

    Thus the minimum number of edges is max(number of vertices with 0 in degree, number of vertices with 0 out degree)

Observation 3:
    If there is only one SCC in the initial graph, the answer is just 0 (edge case).

Note that we don't actually need to make a new adjacency list for the DAG, we can just record which SCC nodes have a non-zero in and out degree.
However, we do this in this code to act as template code for other questions.

Time: O((V + E) log V), Mem: O(V + E). additional log V comes from using set to compress SCC 
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int t, n, e, u, v, dfsNumberCounter, numSCC;
vi dfs_num, dfs_low, visited;
stack<int>st;
vi adjlist[20009];
set<int> adjlist_dag[20009];
vi scc_index, dag_in_degree;

void tarjanSCC(int u){
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;
    dfsNumberCounter++;
    st.push(u);
    visited[u] = 1;

    for (auto v: adjlist[u]){
        if (dfs_num[v] == -1){
            tarjanSCC(v);
        }
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]){
        while (true){
            v = st.top();
            st.pop();
            visited[v] = 0;
            scc_index[v] = numSCC;
            if (v == u)break;
        }
        numSCC++;
    }
}

int main(){
    fast_cin();
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> n >> e;
        scc_index.assign(n, 0);
        dfs_num.assign(n, -1);
        dfs_low.assign(n, 0);
        visited.assign(n, 0);
        dfsNumberCounter = numSCC = 0;
        dag_in_degree.assign(n, 0);
        while (!st.empty())st.pop();
        for (u=0;u<n;u++){
            adjlist[u].clear();
            adjlist_dag[u].clear();
        }
        
        for (int i=0;i<e;i++){
            cin >> u >> v;
            u--; v--;
            adjlist[u].emplace_back(v);
        }

        for (int i=0;i<n;i++){
            if (dfs_num[i] == -1)
                tarjanSCC(i);
        }

        //for (auto i: scc_index){cout << i << " ";}cout << endl;
        // Generate Compressed Graph
        for (u=0; u<n; u++){
            for(auto v: adjlist[u]){
                if (scc_index[v] == scc_index[u])continue;
                //printf("U: %d, V: %d\n", u, v);
                adjlist_dag[scc_index[u]].insert(scc_index[v]);
                dag_in_degree[scc_index[v]] = 1;
            }
        }

        int in_deg_is_0=0, out_deg_is_0=0;
        for (int i=0;i<numSCC;i++){
            //printf("i: %d, dag_in_degree[i]: %d, adjlist_dag[i].size(): %d, \n", i, dag_in_degree[i], (int) adjlist_dag[i].size());
            if (dag_in_degree[i] == 0)in_deg_is_0++;
            if (adjlist_dag[i].size() == 0)out_deg_is_0++;
        }
        //cout << max(out_deg_is_0, in_deg_is_0) << endl;
        
        if (numSCC == 1){
            cout << 0 << endl;
        }
        else{
            cout << max(out_deg_is_0, in_deg_is_0) << endl;
        }
    }

    return 0;
}