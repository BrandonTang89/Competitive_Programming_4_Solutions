/**Kattis - engaging
 * Pretty straightforward problem, only issue is that there is no condition that m <= n all the time,
 * so we need to make 2 different cases (at least because of my shitty library code) for each of them.
 * But the library hungarian algorithm doesn't dissapoint.
 * 
 * Time: O(V^3), Space: O(V^2), V = max(m, n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

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

    void add_edge(int u, int v, ll w) {  // u on the left, v on the right, 0 idx
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

int m, n, k;
vector<vector<int>> adjmat;
int main(){
    cin >> m >> n >> k;
    bool gift_on_left = (m <= n);
    //cout << "gift on left? " << gift_on_left << endl;
    adjmat.assign(m, vector<int>(n, 0)); // adjmat[gift][customer]

    for (int i=0; i< k; i++){
        int cus, gif, sat;
        cin >> cus >> gif >> sat;
        cus--;
        gif--;
        adjmat[gif][cus] = sat;
    }

    hungarian h(min(m, n), max(m, n));
    for (int i=0; i< m; i++){
        for (int j=0; j< n; j++){
            if (gift_on_left){
                h.add_edge(i, j, adjmat[i][j]);
            }
            else{
                h.add_edge(j, i, adjmat[i][j]);
            }
        }
    }

    cout << h.max_matching() << endl;
    vector<int> matching = h.match;
    int L = max(m, n);

    if (gift_on_left){
        int ans = 0;
        for (int i=L; i< 2*L; i++){
            if (matching[i] != -1){
                ans++;
            }
        }
        cout << ans << endl;
        for (int i=L; i< 2*L; i++){
            if (matching[i] != -1){
                cout << i-L+1 << " " << matching[i]+1 << endl;
            }
        }
    }
    else{
        int ans = 0;
        for (int i=0; i<n; i++){
            if (matching[i] != -1){
                ans++;
            }
        }
        cout << ans << endl;
        for (int i=0; i< n; i++){
            if (matching[i] != -1){
                cout << i+1 << " " << matching[i]+1-L << endl;
            }
        }
    }


    return 0;
}