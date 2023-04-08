/**Kattis - delivering
 * Quite a long problem. We start with a Dijkstra on the graph, creating a predecessor adjancency
 * list of the Dijkstra DAG. We then convert it to a successor adjacency list. Then we do a
 * topological sort on the DAG. Then we record down for each node, what clients can be visited
 * before that node on the shortest path to that node (DP according to the DAG topo order). This
 * creates a DAG of clients where u -> v if u can be visited before v. We do minimum vertex cover on
 * this by splitting the DAG into a bipartite graph where the left partition is the out nodes and
 * the right partition is the in nodes then doing MCBM.
 * 
 * Time: O(E Log V + EC + C^3), Space: O(V + E + C)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e, c;
vector<vector<tuple<ll, int>>> adjlist;
vector<vector<tuple<ll, int>>> predecessors;  // w, v
vector<ll> dist;
vector<vector<int>> successors;
priority_queue<tuple<ll, int>, vector<tuple<ll, int>>, greater<tuple<ll, int>>> pq;
vector<int> visited;
vector<int> topo;
vector<unordered_set<int>> DAG_predecessors;
unordered_map<int, int> client_to_node;
vector<int> clients;
vector<vector<int>> AL;

void dfs(int u)
{
    visited[u] = 1;
    for (auto &v : successors[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    topo.push_back(u);
}

vector<int> match;
int aug(int L)
{
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : AL[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}
int cal_MCBM()
{
    match.assign(2 * c, -1);
    unordered_set<int> freeV;
    for (int L = 0; L < c; L++) freeV.emplace(L);
    int MCBM = 0;
    int Vleft = c;  // number of vertices in left partition

    for (int L = 0; L < Vleft; L++) {  // all left vectices
        vector<int> candidates;
        for (auto R : AL[L]) {     // all right vectices neighbouring u
            if (match[R] == -1) {  // if v is unassigned
                candidates.push_back(R);
            }
        }
        if ((int)candidates.size() > 0) {
            MCBM++;
            freeV.erase(L);
            int a = rand() % candidates.size();
            match[candidates[a]] = L;
            match[L] = candidates[a];
        }
    }

    // MCBM Calculation
    for (auto &L : freeV) {
        visited.assign(Vleft, 0);
        MCBM += aug(L);
    }

    return MCBM;
}

int main()
{
    fast_cin();
    cin >> n >> e >> c;
    c++;
    client_to_node[0] = 0;
    clients.assign(c, 0);
    for (int i = 1; i < c; i++) {
        int a;
        cin >> a;
        client_to_node[a] = i;
        clients[i] = a;
    }

    adjlist.assign(n, vector<tuple<ll, int>>());
    for (int i = 0; i < e; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        adjlist[a].push_back({w, b});
    }

    predecessors.assign(n, vector<tuple<ll, int>>());
    dist.assign(n, LONG_LONG_MAX);
    dist[0] = 0;
    pq.push(make_tuple(0, 0));

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;
        for (auto &[w, v] : adjlist[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                predecessors[v].clear();
                predecessors[v].push_back(make_tuple(w, u));
                pq.push(make_tuple(dist[v], v));
            }
            else if (dist[v] == dist[u] + w) {
                predecessors[v].push_back(make_tuple(w, u));
            }
        }
    }

    successors.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (auto &[w, v] : predecessors[i]) {
            successors[v].push_back(i);
        }
    }

    visited.assign(n, 0);
    dfs(0);
    reverse(topo.begin(), topo.end());
    DAG_predecessors.assign(n, unordered_set<int>());

    for (int i = 0; i < n; i++) {
        int u = topo[i];
        for (auto v : successors[u]) {
            for (auto p : DAG_predecessors[u]) {
                DAG_predecessors[v].insert(p);
            }
            if (client_to_node.find(u) != client_to_node.end()) {
                DAG_predecessors[v].insert(client_to_node[u]);
            }
        }
    }

    AL.assign(c * 2, vector<int>());
    for (int i = 0; i < c; i++) {
        for (auto u : DAG_predecessors[clients[i]]) {
            AL[i].push_back(u + c);
            AL[u + c].push_back(i);
        }
    }

    cout << c - cal_MCBM() << endl;

    return 0;
}