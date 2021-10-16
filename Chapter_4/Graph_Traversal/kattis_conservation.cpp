/* Kattis - Conservation
A topological sort question where we try to do all the nodes at each lab which are possible before moving over to the other lab.
We accomplish this with the use of 2 separate queues that store the possible processes for each lab

Time: O(V + E), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int t, n, e, u, v;
int required_lab[100009], in_degree[100009], temp_int_degree[100009]; // used by the algorithm and reset 
vector<int> adjlist[100009];
queue<int> q1, q2; // queues for 1 and 2

int kahn(bool starting_lab_1){
    // Initialise the queues
    for(u=0;u<n;u++){
        temp_int_degree[u] = in_degree[u];
        if (in_degree[u] == 0){
            if (required_lab[u] == 1){
                q1.push(u);
            }
            else{
                q2.push(u);
            }
        }
    }

    bool lab1 = starting_lab_1; // are we grabbing from lab1?
    int swaps = 0;
    while (!q1.empty() || !q2.empty()){
        if (lab1){
            if(q1.empty()){
                lab1 = false;
                swaps++;
                continue;
            }
            u = q1.front();
            q1.pop();
        }
        else{
            if(q2.empty()){
                lab1 = true;
                swaps++;
                continue;
            }
            u = q2.front();
            q2.pop();
        }
        for (auto v: adjlist[u]){
            temp_int_degree[v]--;
            if (temp_int_degree[v] == 0){
                if (required_lab[v] == 1){
                    q1.push(v);
                }
                else{
                    q2.push(v);
                }
            }
        }
    }

    return swaps;
}

int main(){
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> n >> e;
        for (int i=0;i<n;i++){
            cin >> required_lab[i];
            adjlist[i].clear();
            in_degree[i] = 0;
        }
        
        for (int i=0;i<e;i++){
            cin >> u >> v;
            u--; v--;

            in_degree[v]++;
            adjlist[u].emplace_back(v);
        }
        cout << min(kahn(0), kahn(1)) << endl; // minimum starting from each lab
    }

    return 0;
}