/* kattis - allpairspath
What supposed to be a "simple" problem might be hard to debug for some reasons
1. There exist self loops... which can be both positive or negative
2. The graph is not simple, we need to get the minimum of all edges between u->v (u can == v)

So how do we deal with the whole "negative inf" thing? well, we already know what nodes are part
of negative cycles. So we can go from u to k (part of a neg cycle) and from k to v, then the path
from u to v can be infinitely short!

Time: O(V^3), Mem: O(V^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int INF = (int) 1e9;
vector<vector<int>> adjmat;
vector<int> part_of_neg_cycle;
int n, e, u, v, w, q;
int main(){
    fast_cin();
    while (true){
        cin >> n >> e >> q;
        if (n == 0 && e == 0)break;
        adjmat.assign(n, vector<int>(n, INF));
        part_of_neg_cycle.clear();
        for (int i=0;i<n;i++){
            adjmat[i][i] = 0;
        }
        for (int i=0;i<e;i++){
            cin >> u >> v >> w;
            adjmat[u][v] = min(adjmat[u][v], w);
        }
        for (int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if ((adjmat[i][k] == INF) || (adjmat[k][j] == INF))continue;
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }

        for (int i=0;i<n;i++){
            if (adjmat[i][i] < 0){
                part_of_neg_cycle.emplace_back(i);
                // cout << "PART OF NEG CYCLE: " << i << endl;
            }
        }
        
        for (int q_num = 0; q_num < q; q_num++){
            cin >> u >> v;

            bool neg_inf = false;
            for (auto k: part_of_neg_cycle){
                if ((adjmat[u][k] < INF) && (adjmat[k][v] < INF)){ 
                    // there exist a path from u to v through k
                    neg_inf = true;
                    //cout << "passing through k: " << k << endl;
                    break; 
                }
            }

            if (neg_inf){
                cout << "-Infinity" << endl;
            }
            else if (adjmat[u][v] == INF){
                cout << "Impossible" << endl;
            }
            else{
                cout << adjmat[u][v] <<endl;
            }
        }

        cout << endl;
        
    }

    return 0;
}