/**Kattis - gravamen
 * A good problem. BSTA + Max Flow + Print solution. So we BSTA for the maximum wins each legal
 * entity can have. Then we do some max flow modelling: Connect a source to each legal entity via an
 * edge of weight (max wins). Then each lawsuit is represented by a node with 2 edges in, one from
 * each the parities, with weight 1. Each lawsuit has 1 out-edge, of weight 1, to the sink. We carry
 * out maxflow and see if we get L flow. Which indicates we can have <= max_wins as our answer. Once
 * we have the minimum maximum number of wins, we get the solution by modifying the add edge method
 * to return labels to the interesting edges and implement a get_wins method to determine for each
 * law suit, which of the in-edges have flow (which will represent which of the parties wins).
 *
 * Time: O(log L * VE), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e18;  // large enough

int R, S, L;
vector<pair<int, int>> suits;
vector<pair<int, int>> suit_edge_labels;
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
    int add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return -1;                    // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index

        return EL.size() - 2;  // return index of u->v edge
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

    vector<bool> get_wins() {
        vector<bool> ans(L, false);  // left wins if true
        for (int i = 0; i < L; i++) {
            auto &[r_label, s_label] = suit_edge_labels[i];
            auto &[v, cap, flow] = EL[r_label];
            if (flow == 1) {    // there's flow --> assignment exists
                ans[i] = true;  // task v has been assigned to person i
            }
        }
        return ans;
    }
};

pair<bool, vector<bool>> check_valid(int max_wins) {
    max_flow G = max_flow(R + S + L + 2);
    for (int i = 0; i < L; i++) {
        auto &[r, s] = suits[i];
        int a = G.add_edge(r, R + S + i + 1, 1);
        int b = G.add_edge(R + s, R + S + i + 1, 1);
        suit_edge_labels[i] = {a, b};
        G.add_edge(R + S + i + 1, R + S + L + 1, 1);
    }

    for (int i = 0; i < R + S; i++) {
        G.add_edge(0, i + 1, max_wins);
    }

    return {(G.dinic(0, R + S + L + 1) == L), G.get_wins()};
}
int main() {
    cin >> R >> S >> L;
    suits.resize(L);
    suit_edge_labels.resize(L);

    for (int i = 0; i < L; i++) {
        int r, s;
        cin >> r >> s;
        suits[i] = {r, s};
    }

    int lo = 1, hi = L;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (check_valid(mid).first) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    if (lo < hi) {
        if (check_valid(lo).first) hi = lo;
    }

    vector<bool> left_wins = check_valid(hi).second;
    for (int i = 0; i < L; i++) {
        if (left_wins[i]) {
            cout << "INDV " << suits[i].first << endl;
        } else {
            cout << "CORP " << suits[i].second << endl;
        }
    }

    return 0;
}