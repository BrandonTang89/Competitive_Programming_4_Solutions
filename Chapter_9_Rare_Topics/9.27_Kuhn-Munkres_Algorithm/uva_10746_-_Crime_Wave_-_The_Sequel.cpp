#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld big_num = 1e15, INF = 1e18, EPS = 1e-9;
class hungarian {  // Hungarian algorithm to find the maximum value PERFECT matching
   private:
    int L, V;
    int real_L;
    vector<vector<ld>> adjmat;
    vector<ld> l;       // labels
    vector<int> visited;
    vector<int> S;  // vertices along the (partial) augmenting path
    unordered_set<int> notT;  // vertices not in T
    unordered_set<int> T;     // vertices in T

    void expand_equality_subgraph() {
        ld min_delta = INF;
        for (auto x : S) {
            for (auto y : notT) {
                min_delta = min(min_delta, -adjmat[x][y - L] + l[x] + l[y]);
            }
        }
        assert(min_delta != INF);
        for (auto x : S) {
            l[x] -= min_delta;
        }
        for (auto y : T) {
            l[y] += min_delta;
        }
    }

    int aug(int x) {
        if (visited[x]) return 0;
        visited[x] = 1;
        S.push_back(x);
        for (int y = L; y < V; y++) {
            if (fabs(l[x] + l[y] - adjmat[x][y - L]) > EPS)
                continue;  // not part of equality subgraph
            
            T.insert(y);
            notT.erase(y);
            if (match[y] == -1 || aug(match[y])) {
                match[y] = x;
                match[x] = y;
                return 1;
            }
        }
        return 0;
    }

   public:
    vector<int> match;  // match[i] = j means i is matched with j
    // Call hungarian with L <= R ie we try to match all the left vertices
    hungarian(int initL, int initR) : L(initR), V(2 * initR), real_L(initL) {
        // left from 0 to L-1, right from L to 2L-1, vertices real_L to L-1 are dummy
        adjmat.assign(L, vector<ld>(L, -big_num));
        // Augment no-edge to be a large negative value
        // admat[i][j] is the edge weight from i to L+j
    }

    void add_edge(int u, int v, ld w) { // u on the left, v on the right
        v -= L;
        adjmat[u][v] = w;
    }

    ld max_matching() {
        l.assign(V, 0);  // each right vertex starts with label 0
        for (int i = 0; i < L; i++) {
            // for each left vertex, assign label to the the largest weight edge
            l[i] = -INF;
            for (int j = 0; j < L; j++) {
                l[i] = max(l[i], adjmat[i][j]);
            }
        }
       
        match.assign(V, -1);
        for (int i = 0; i < real_L; i++) {
            assert(match[i] == -1);
            
            while (1){
                S.clear();
                T.clear();
                notT.clear();
                for (int j = L; j < V; j++) {
                    notT.insert(j);
                }
                visited.assign(L, 0);
                int res = aug(i);
                if (res)break;
                // Else we need to expand the equality subgraph
                expand_equality_subgraph();
            }
        }
        ld totalmatching = 0;
        for (int i = 0; i < real_L; i++) {
            assert(match[i] != -1);
            totalmatching += adjmat[i][match[i] - L];
        }

        return totalmatching;
    }
};

int L, R;
int main() {
    while (1) {
        cin >> L >> R;
        if (L == 0 && R == 0) break;
        hungarian h(L, R); // L <= R

        for (int x = 0; x < L; x++) {
            for (int y = R; y < 2 * R; y++) {
                ld w;
                cin >> w;
                h.add_edge(x, y, -w);
            }
        }
        ld flowCost = -h.max_matching() / ((ld)L);
		flowCost = floor(flowCost*100.0+0.5+1e-9)/100.0;
		printf("%.2Lf\n",flowCost);
    }
    return 0;
}