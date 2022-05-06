/**Kattis - cordonbleu
 * Graph modelling + hungarian algorithm. Notice that all bottles will do the trip from their location to the
 * restaurant somehow or another, so we can just compute the sum of those distances first. Then now we need to
 * find the lowest cost way to reach each bottle. Notice that the possible locations to travel to the bottles
 * are the restaurant and the courier initial locations. Observe further that we can have at most N-1 times
 * that a courier comes from the restaurant (unless a courier starts there). As such, we model the problem
 * as a weighted MCBM where the left set is the bottles and the right set is the couriers + n-1 copies of the
 * restaurant. A match (u, v) means bottle u is picked up from location v.
 * 
 * Time can be tight with a non-optimised Hungarian algorithm library code.
 * 
 * Time: O(V^3), Space: O(V^2), V = 2*n + m
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
typedef vector<int> vi;

const ll big_num = 1e15, INF = 1e18;  // bin_num > max_weight*R
class hungarian {  // Hungarian algorithm to find the maximum value PERFECT matching
   private:
    int L, V;
    int real_L, visited_cnt;  // increment visited_cnt before every caint of aug
    vector<vector<ll>> adjmat;
    vector<ll> l;  // labels
    vector<int> visited;
    vector<int> S;  // vertices along the (partial) augmenting path
    vector<int>
        inT;  // 1 if index in t, else 0. T is the set of vertices ajacent to augmenting path

    void expand_equality_subgraph() {
        ll min_delta = INF;
        for (const int &x : S) {
            for (int i = 0; i < L; i++) {
                if (inT[i] == 1) continue;  // we want not in T
                min_delta = min(min_delta, -adjmat[x][i] + l[x] + l[i + L]);
            }
        }
        for (const int &x : S) {
            l[x] -= min_delta;
        }
        for (int i = 0; i < L; i++) {
            if (inT[i] == 0) continue;  // we want in T
            l[i + L] += min_delta;
        }
    }

    int aug(int x) {
        if (visited[x] == visited_cnt) return 0;
        visited[x] = visited_cnt;
        S.push_back(x);
        for (int y = L; y < V; y++) {
            if (l[x] + l[y] != adjmat[x][y - L]) continue;  // not part of equality subgraph
            // Edit condition if used for floats

            inT[y - L] = 1;
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
        adjmat.assign(L, vector<ll>(L, -big_num));
        // Augment no-edge to be a large negative value
        // admat[i][j] is the edge weight from i to L+j
    }

    void add_edge(int u, int v, ll w) {  // u on the left, v on the right, 0 index
        adjmat[u][v] = w;
    }

    int max_matching() {
        l.assign(V, 0);  // each right vertex starts with label 0
        visited.assign(L, 0);
        visited_cnt = 0;
        for (int i = 0; i < L; i++) {
            // for each left vertex, assign label to the the largest weight edge
            l[i] = -INF;
            for (int j = 0; j < L; j++) {
                l[i] = max(l[i], adjmat[i][j]);
            }
        }

        match.assign(V, -1);
        for (int i = 0; i < real_L; i++) {
            if (match[i] != -1) continue;
            while (1) {
                S.clear();
                inT.assign(L, 0);
                visited_cnt++;
                int res = aug(i);
                if (res) {
                    break;
                }
                // Else we need to expand the equality subgraph
                expand_equality_subgraph();
            }
        }
        ll totalmatching = 0;
        for (int i = 0; i < real_L; i++) {
            totalmatching += adjmat[i][match[i] - L];
        }

        return totalmatching;
    }
};

int inline manhattan(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
int main() {
    fast_cin();
    int num_b, num_c;  // num bottles, num couriers
    cin >> num_b >> num_c;
    int resx, resy;

    vector<pair<int, int>> bottles, couriers;
    for (int i = 0; i < num_b; i++) {
        int x, y;
        cin >> x >> y;
        bottles.push_back(make_pair(x, y));
    }
    for (int i = 0; i < num_c; i++) {
        int x, y;
        cin >> x >> y;
        couriers.push_back(make_pair(x, y));
    }
    cin >> resx >> resy;
    for (int i = 0; i < num_b - 1; i++) {
        couriers.push_back(make_pair(resx, resy));
    }

    hungarian h(num_b,
                num_b + num_c - 1);  // all bottles, all couriers + n-1 clones of the restaurant

    int R = num_b + num_c - 1;
    for (int i = 0; i < num_b; i++) {
        for (int j = 0; j < R; j++) {
            h.add_edge(i, j, -manhattan(bottles[i], couriers[j]));
        }
    }

    int ans = -h.max_matching();
    for (int i = 0; i < num_b; i++) {
        ans += manhattan(bottles[i], {resx, resy});
    }
    cout << ans << endl;
    return 0;
}