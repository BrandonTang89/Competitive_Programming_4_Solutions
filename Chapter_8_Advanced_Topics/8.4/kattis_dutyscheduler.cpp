/**Kattis - dutyscheduler
 * My first max flow problem (excluding that one time i did it in CS3233 2018). Here we are doing an assignment
 * problem and printing the solution. Model the problem as all the RAs form a left partition of a bipartite graph,
 * all the days form the right partition. All nodes in the left are conencted to a source by capacity K, all nodes
 * on the right are connected with capacity 2. If we can have max flow = R*2, then we can have each RA only doing 
 * K days, We can now BSTA for K, or just try it linearly because K is small.
 * 
 * Time: O(R*(R+L)^2*(E)), Space: O(V+E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e18;  // large enough

class max_flow {
   private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {  // find augmenting path
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});  // record BFS sp tree
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;                                    // stop as sink t reached
            for (auto &idx : AL[u]) {                             // explore neighbors of u
                auto &[v, cap, flow] = EL[idx];                   // stored in EL[idx]
                if ((cap - flow > 0) && (d[v] == -1))             // positive residual edge
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};  // 3 lines in one!
            }
        }
        return d[t] != -1;  // has an augmenting path
    }

    ll DFS(int u, int t, ll f = INF) {  // traverse from s->t
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {  // from last edge
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1) continue;  // not part of layer graph
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);  // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

   public:
    max_flow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return;                       // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index
    }

    ll dinic(int s, int t) {
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }

    // Get Non-Zero Flow between Left and Right Partitions (assignment problem solution)
    // Source == 0, left is [1, L], right is [L+1, L+R], Sink is L+R+1
    // Add edges in the correct order!
    vector<pair<int, int>> get_assignment(int L, int R) {
        vector<pair<int, int>> assignment;
        for (int i = 1; i <= L; ++i) {
            for (auto &idx : AL[i]) {
                auto &[v, cap, flow] = EL[idx];
                if (flow == 1) {                   // there's flow --> assignment exists
                    assignment.push_back({v, i});  // task v has been assigned to person i
                }
            }
        }
        return assignment;
    }
};

int L, R, v;
string names[61];
vector<int> adjlist[61];
int main() {
    int k;
    cin >> L >> R;

    for (int i = 1; i <= L; i++) {
        cin >> names[i];
        cin >> k;  // number of neigbours
        for (int j = 0; j < k; j++) {
            cin >> v;
            adjlist[i].push_back(v);
        }
    }

    for (int ans = 1; ans <= R; ans++) {
        max_flow G(L + R + 2);
        for (int i = 1; i <= L; i++) {
            G.add_edge(0, i, ans);
        }
        for (int i = 1; i <= L; i++) {
            for (auto j : adjlist[i]) {
                G.add_edge(i, L + j, 1);
            }
        }
        for (int i = L + 1; i <= L + R; i++) {
            G.add_edge(i, L + R + 1, 2);
        }

        ll flow = G.dinic(0, L + R + 1);
        if (flow == 2 * R) {
            cout << ans << endl;
            auto assignment = G.get_assignment(L, R);
            sort(assignment.begin(), assignment.end());
            for (int i = 0; i < (int)assignment.size(); i += 2) {
                int day = assignment[i].first;
                int a = assignment[i].second;
                int b = assignment[i + 1].second;
                cout << "Day " << day - L << ": " << names[a] + " " + names[b] << endl;
            }
            break;
        }
    }
    return 0;
}