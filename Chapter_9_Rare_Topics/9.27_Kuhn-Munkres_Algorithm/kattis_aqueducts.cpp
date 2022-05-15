/**Kattis - aqueducts
 * Graph modelling + Floyd Warshall's APSP + Weighted MCBM with Hugarian Algorithm.
 * Note that the length between each direct edge is <= q, but we can join multiple components to get from 1
 * spring to 1 town. We can also have distinct aqueducts passing through the same hill (regardless of whether
 * the hill is used as a town or spring or none or whether there is any other ducts passing over it).
 * 
 * Time: O(V^3), Space: O(V^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld big_num = 1e14, INF = 1e18, EPS = 1e-9;
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
        // assert(min_delta != INF);
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
        // cout << "adding " << u << " " << v << " " << w << endl;
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
            //assert(match[i] == -1);
            
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
            //assert(match[i] != -1);
            totalmatching += adjmat[i][match[i] - L];
        }

        return totalmatching;
    }
};

int L, R;
int main() {
    
    int n, s, t, q;
    cin >> n >> s >> t >> q; // t <= s
    vector<tuple<ld, ld, ld>> hills;
    for (int i=0; i<n; i++){
        ld x, y, h;
        cin >> x >> y >> h;
        hills.push_back(make_tuple(x, y, h));
    }
    vector<int>  springs, towns;
    springs.resize(s);
    for(int i=0; i<s; i++){
        cin >> springs[i];
        springs[i]--;
    }
    towns.resize(t);
    for(int i=0; i<t; i++){
        cin >> towns[i];
        towns[i]--;
    }

    hungarian h(t, s); // try to match each town to each spring

    vector<vector<ld>> adjmat(n, vector<ld>(n, INF));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j)continue;
            ld x1, y1, h1, x2, y2, h2;
            tie(x1, y1, h1) = hills[i];
            tie(x2, y2, h2) = hills[j];

            // see if we can put a duct from h1 to h2
            if (h1 <= h2)continue;
            ld dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (h1-h2)*(h1-h2));
            // cout << "dist " << dist << endl;
            if (dist < q + EPS) {
                adjmat[i][j] = dist;
            }
        }
    }

    // floyd warshall
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
            }
        }
    }

    for (int ti = 0; ti < t; ti++) {
        for (int si = 0; si < s; si++) {
            int spring = springs[si];
            int town = towns[ti];
            if (fabs(adjmat[spring][town] - INF) > EPS) {
                h.add_edge(ti, si+s, -adjmat[spring][town]);
            }
        }
    }
    cout << fixed << setprecision(10); 
    
    ld ans = -h.max_matching();
    if (ans > big_num) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}