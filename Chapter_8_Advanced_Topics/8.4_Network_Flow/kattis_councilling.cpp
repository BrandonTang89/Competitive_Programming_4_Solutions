/**Kattis - councilling
 * Relatively classic max flow modelling + checking which edges have flow. A lot of work is put into
 * parsing the input properly and doing mappings from string to indices. The modelling is as
 * follows:
 *
 * src is connected to each club by a weight 1 edge each. This ensures each club only has 1
 * representative. Each club is connected to the people in it by edges of weight 1 (though this
 * weight is arbitary since adjacent edges are already weight 1). Each person is connected to their
 * political party by edges of weight 1. This ensures that each person only represents 1 club. Each
 * political party is connected to the sink by edges of weight (n-1)//2. This ensures that we can
 * have up to (n-1)//2 people in each political party in the council.
 *
 * Then we just maxflow from source to sink and check if this is equal to the number of clubs. If
 * so, we check the edges between the clubs and people and see which have flow.
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;  // number of people
int numpp, numClubs;
unordered_map<string, int> clubNametoIndex;
vector<string> clubIndextoName;
vector<vector<int>> clubPeople;  // clubPeople[i] = list of people in club i

vector<int> personspp;
vector<string> personIndextoName;

unordered_map<string, int> ppNametoIndex;

class max_flow {
   private:
    int V;
    vector<edge> EL;
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

    ll getFlow(int edgeLabel) { return get<2>(EL[edgeLabel]); }
};

int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        numpp = 0;
        numClubs = 0;
        clubNametoIndex.clear();
        clubIndextoName.clear();
        clubPeople.clear();
        personspp.assign(n, -1);
        personIndextoName.clear();
        ppNametoIndex.clear();
        for (int i = 0; i < n; i++) {
            string name, pp;
            cin >> name >> pp;
            personIndextoName.push_back(name);

            if (ppNametoIndex.find(pp) == ppNametoIndex.end()) {
                ppNametoIndex[pp] = numpp;
                numpp++;
            }
            personspp[i] = ppNametoIndex[pp];

            int curClubs;
            cin >> curClubs;
            for (int j = 0; j < curClubs; j++) {
                string clubName;
                cin >> clubName;
                if (clubNametoIndex.find(clubName) == clubNametoIndex.end()) {
                    clubNametoIndex[clubName] = numClubs;
                    clubIndextoName.push_back(clubName);
                    clubPeople.push_back(vector<int>());
                    numClubs++;
                }
                clubPeople[clubNametoIndex[clubName]].push_back(i);
            }
        }

        int numVertices = 2 + numpp + numClubs + n;
        int src = numVertices - 2;
        int sink = numVertices - 1;
        int partyWeight = (numClubs - 1) / 2;

        max_flow mf(numVertices);
        for (int i = 0; i < numClubs; i++) {
            mf.add_edge(src, i, 1);
        }
        for (int i = 0; i < n; i++) {
            mf.add_edge(numClubs + i, numClubs + n + personspp[i], 1);
        }
        for (int i = 0; i < numpp; i++) {
            mf.add_edge(numClubs + n + i, sink, partyWeight);
        }

        vector<tuple<int, int, int>> clubPeopleEdges;  // club, person, edge
        for (int i = 0; i < numClubs; i++) {
            for (int j = 0; j < (int)clubPeople[i].size(); j++) {
                clubPeopleEdges.push_back(make_tuple(
                    i, clubPeople[i][j], mf.add_edge(i, numClubs + clubPeople[i][j], 1)));
            }
        }

        ll totalFlow = mf.dinic(src, sink);
        if (totalFlow != numClubs) {
            cout << "Impossible.\n";
            if (tc > 0) cout << "\n";
            continue;
        }

        int numFlow = 0;
        for (auto &[club, person, edge] : clubPeopleEdges) {
            if (mf.getFlow(edge) > 0) {
                cout << personIndextoName[person] << " " << clubIndextoName[club] << "\n";
                numFlow++;
            }
        }
        assert(numFlow == numClubs);
        if (tc > 0) cout << "\n";
    }

    return 0;
}