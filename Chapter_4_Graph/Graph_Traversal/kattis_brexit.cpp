/* Kattis - brexit
Observation 1:
    To determine if a country will leave at a specific time, we just check its degree to see if it is <= half of its starting degree. 
    However, it will be too inefficient to check all nodes for every deleted node, thus we note that
    If a certain country leaves, only its neighbours will be directly affected. Thus, we only need to check those nodes.

    we can use a queue data structure to keep track of currently leaving countries and process the leaving countries one by one, adding
    more leaving countries as they come.

Time: O(E + V), Mem: O(E + V)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, x, l;
bool state[200009];
int lde[200009], deg[200009]; //state 0: there, 1: inqueue or left; leaving degree, current degreee
vector<int> adjlist[200009]; 
queue<int> q;

int main(){
    fast_cin();
    cin >> n >> e >> x >> l;
    x--; 
    l--;

    for (int i=0;i<e;i++){
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);

        deg[u]++;
        deg[v]++;
        lde[u]++;
        lde[v]++;
    }
    for (int i=0;i<n;i++){
        lde[i] /= 2;
    }

    q.push(l);
    state[l] = 1;
    for (int u = q.front(); !q.empty(); u=q.front()){
        q.pop(); //get rid of first element, we process it now
        
        for (auto v: adjlist[u]){
            if (state[v] == 1)continue;
            deg[v]--; 
            if (deg[v] <= lde[v]){ // this country leaves too
                state[v] = 1;
                q.push(v);
            }
        }
    }

    cout << (state[x] ? "leave" : "stay") << endl;

    return 0;
}