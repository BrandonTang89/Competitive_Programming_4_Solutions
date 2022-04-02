/**Kattis - reactivity
 * We are determining if there exist a hamiltonian path in the DAG. To do this, we determine
 * if there is only 1 valid topological sort of the DAG using 2 runs of Khan's Algorithm.
 * 
 * Time: O(V + E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, e, u, v;
vector<int> adjlist[1001];
vector<int> ts, ts2, in_degree, in_degree2;
priority_queue<int, vector<int>, greater<int>> pq;  // min priority queue
priority_queue<int> pq2;                            // max priority queue
int main() {
    cin >> n >> e;
    in_degree.assign(n, 0);
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adjlist[u].push_back(v);
        in_degree[v]++;
    }
    in_degree2 = in_degree;

    for (int u = 0; u < n; ++u)
        if (in_degree[u] == 0)  // next to be processed
            pq.push(u);         // smaller index first

    while (!pq.empty()) {  // Kahn's algorithm
        int u = pq.top();
        pq.pop();

        ts.emplace_back(u);  // u is next in topo sort
        for (auto &v : adjlist[u]) {
            --in_degree[v];                  // virtually remove u->v
            if (in_degree[v] > 0) continue;  // not a candidate, skip
            pq.push(v);                      // enqueue v in pq
        }
    }
    for (int u = 0; u < n; ++u)
        if (in_degree2[u] == 0)  // next to be processed
            pq2.push(u);         // larger index first

    while (!pq2.empty()) {  // Kahn's algorithm
        int u = pq2.top();
        pq2.pop();

        ts2.emplace_back(u);  // u is next in topo sort
        for (auto &v : adjlist[u]) {
            --in_degree2[v];                  // virtually remove u->v
            if (in_degree2[v] > 0) continue;  // not a candidate, skip
            pq2.push(v);                      // enqueue v in pq
        }
    }

    if (ts == ts2){
        for (auto &x : ts)
            cout << x << " ";
        cout << endl;
    }
    else{
        cout << "back to the lab" << endl;
    }

    return 0;
}