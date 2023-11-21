/**Kattis - fakescoreboard
 * Max-flow problem with lexicographically minimum assignment. The problem of finding any set S of
 * {(team, problem)} such that S satisfies all the team and problem constraints is simple. We just
 * create a graph with a node for each team, a node for each problem, and a source and a sink. We
 * add edges of weight (score of team) from the source to each team, edges of weight (score of
 * problem) from each problem to each team, and we add a dense layer of edges of weight 1 from each
 * team to each problem. We then find the max-flow and see if that is equal to the sum of the scores
 * of all the teams.
 *
 * However, the issue we need to scoreboard that is lexicographically smallest. This means that we
 * should try to get the first team to not solve the first problem if possible. Then get the first
 * team to not solve the second problem if possible, and so on.
 *
 * We can force the ith team to not solve the jth problem by reducing the capacity of the relevant
 * edge (i*p+j) between the first team and the first problem from 1 to 0. Then, if that edge was
 * initially used, we need to adjust all the flows along the path of the flow that initially passed
 * through the edge we just removed. Fortunately, there is only 1 possible path for such a flow to
 * occur, specifically: from src to the team, across the edge, to the problem, to the sink. So we
 * decrement all the flows of forward edges along this path and increment all the flows of backward
 * edges along this path. Then we run max-flow again and see if we get 1 more flow. If we do, then
 * we know that we don't need that edge. Else, since theres no augmenting path, the state of our
 * max_flow instance didn't change and we just reverse everything we did.
 *
 * (Actually, even if we don't deal with the back edges,
 * we will AC due to coincidences in the structure of the graph and what we are trying to do (only
 * send 1 flow), but it is good practice to do so to maintain the data structure invariants of the
 * max_flow object) 
 * 
 * Note that since the maximum augmenting flow is O(pt), the complexity of running
 * Dinic's algorithm initially is also O(pt).
 *
 * Time: O(pt), Space: O(pt)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;  // <dest, cap, flow>
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e18;  // large enough
class max_flow {
   private:
    int V;

    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t)
    {  // find augmenting path
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

    ll DFS(int u, int t, ll f = INF)
    {  // traverse from s->t
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
    vector<edge> EL;
    max_flow(int initialV) : V(initialV)
    {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    int add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v) return -1;                    // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index

        return EL.size() - 2;  // return index of u->v edge
    }

    ll getFlow(int edgeLabel) { return get<2>(EL[edgeLabel]); }

    ll dinic(int s, int t)
    {
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int t, p, src, sink;
unordered_set<int> notUsed;
vector<int> teamScores, problemScores;
vector<int> edgeIndices, teamIndices, problemIndices;
int main()
{
    while (1) {
        cin >> t >> p;
        if (t == 0 && p == 0) break;
        notUsed.clear();
        teamScores.assign(t, 0);
        problemScores.assign(p, 0);
        for (int i = 0; i < t; i++) {
            cin >> teamScores[i];
        }
        for (int i = 0; i < p; i++) {
            cin >> problemScores[i];
        }

        int requiredFlow = accumulate(teamScores.begin(), teamScores.end(), 0);
        int problemSum = accumulate(problemScores.begin(), problemScores.end(), 0);

        if (requiredFlow != problemSum) {
            cout << "Impossible" << endl << endl;
            continue;
        }

        max_flow mf(t + p + 2);
        src = t + p, sink = t + p + 1;

        edgeIndices.assign(t * p, -1);
        teamIndices.assign(t, -1);
        problemIndices.assign(p, -1);
        for (int i = 0; i < t; i++) {
            teamIndices[i] = mf.add_edge(src, i, teamScores[i]);
        }
        for (int i = 0; i < p; i++) {
            problemIndices[i] = mf.add_edge(i + t, sink, problemScores[i]);
        }
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < p; j++) {
                int idx = i * p + j;
                if (notUsed.find(idx) == notUsed.end()) {
                    edgeIndices[idx] = mf.add_edge(i, j + t, 1);
                }
            }
        }
        int maxFlow = mf.dinic(src, sink);
        if (maxFlow != requiredFlow) {
            cout << "Impossible" << endl << endl;
            continue;
        }

        // Inv: maxFlow == requiredFlow
        for (int i = 0; i < p * t; i++) {
            notUsed.insert(i);
            // Lets attempt to not use edge i

            auto &[u, cap, flow] = mf.EL[edgeIndices[i]];
            cap = 0;
            if (mf.getFlow(edgeIndices[i]) == 0) {
                continue;
            }
            flow = 0;
            auto &rflow = get<2>(mf.EL[edgeIndices[i] ^ 1]);  // back edge
            rflow = 0;
            int team = i / p;
            int problem = i % p;

            // remove the flow from src to team and from problem to sink
            auto &[u2, cap2, flow2] = mf.EL[teamIndices[team]];
            flow2 -= 1;
            auto &rflow2 = get<2>(mf.EL[teamIndices[team] ^ 1]);
            rflow2 += 1;

            auto &[u3, cap3, flow3] = mf.EL[problemIndices[problem]];
            flow3 -= 1;
            auto &rflow3 = get<2>(mf.EL[problemIndices[problem] ^ 1]);
            rflow3 += 1;

            int newFlow = mf.dinic(src, sink);
            if (newFlow != 1) {  // no possible augmenting path so nothing has changed
                notUsed.erase(i);

                // add back the flow from src to team and from problem to sink
                flow2 += 1;
                flow3 += 1;
                rflow2 -= 1;
                rflow3 -= 1;
                cap = 1;
                flow = 1;
                rflow = -1;
            }
        }

        // Inv: maxFlow == requiredFlow && notUsed contains all the edges that are not used
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < p; j++) {
                int idx = i * p + j;
                if (notUsed.find(idx) != notUsed.end()) {
                    cout << "N";
                }
                else {
                    cout << "Y";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}