/* Kattis - minspantree
This problem is simply asking us to generate a minimum spanning tree if possible and detect
if it is not. Using a modified prim's algorithm, this problem is very standard.

Time: O(E log V), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, w;
vector<vector<tuple<int,int>>> adjlist; 
vi taken;
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int> >, greater<tuple<int,int,int> > > pq;
vector<tuple<int,int>> mst_el;

void process(int u){
    taken[u] = 1;
    for (auto &[w, v]: adjlist[u]){
        if (!taken[v])
            pq.emplace(w, v, u);
    }
}

int main(){
    fast_cin();
    while(true){
        cin >> n >> e;
        if (n == 0 && e == 0)break;

        // reset variables
        taken.assign(n, 0);
        adjlist.assign(n, vector<tuple<int,int>>());
        mst_el.clear();
        while (!pq.empty()){pq.pop();}

        for (int i=0;i<e;i++){
            cin >> u >> v >> w;
            adjlist[u].emplace_back(w, v);
            adjlist[v].emplace_back(w, u);
        }

        ll mst_cost = 0, num_taken = 0;
        process(0);
        while (!pq.empty()){
            auto [w, u, p] = pq.top(); // p -> u is an MST edge 
            pq.pop();
            if (taken[u])continue;

            // We take the current edge in the MST
            mst_cost+=w;
            mst_el.emplace_back(min(u, p), max(u, p));
            num_taken++;

            // Propagate from u
            process(u);

            if (num_taken == n-1)break;
        }

        if (num_taken != n-1){
            cout << "Impossible" << endl;
        }
        else{
            cout << mst_cost << endl; 
            sort(mst_el.begin(), mst_el.end());
            for (auto [u,v]: mst_el){
                cout << u << " " << v << endl;
            }
        }
    }

    return 0;
}