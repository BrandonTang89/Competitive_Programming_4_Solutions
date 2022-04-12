/**Kattis - carpool
 * Decent question. First we APSP Floyd-warshall on the small V<=17 graph. Then we use DP
 * on 2 functions. The first function determins the minimum cost of a trip with a given set
 * of passengers. We try up to 5! permutations of going to the different places. The second
 * is the overall bigger function that tries to assign every valid subset of passengers to
 * a trip and gets the best option.
 * 
 * Also there might be parallel edges (and maybe even selfloops?) take the minimum weight edge
 * during input.
 * 
 * Time: O(?) Not easy to determine time since the number of transitions is inconsistent
 * Space: O(2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define LSOne(S) (S & (-S))
int n, e;
ll INF = 1e10;
vector<vector<ll>> adjmat;

ll memo2[(1 << 15) + 1];
ll cost_of_trip(int mask){ // mask contains the people in the car, at most 5 1s
    if (memo2[mask] != -1) return memo2[mask];
    vector<int> locs;
    for (int bm=mask;bm; bm-=LSOne(bm)){
        locs.push_back(__builtin_ctz(bm)+1); // offset by 1
    }
    ll min_cost = INF;
    do {
        ll cost = adjmat[0][locs[0]];
        for (int i = 1; i < (int) locs.size(); i++){
            cost += adjmat[locs[i-1]][locs[i]];
        }
        cost += adjmat[locs[locs.size()-1]][n+1];
        min_cost = min(min_cost, cost);
    } while (next_permutation(locs.begin(), locs.end()));

    return memo2[mask] = min_cost + 5*(locs.size());
}


ll memo[(1 << 15) + 1][4];
ll dp(int mask, int num_cars){

    if (memo[mask][num_cars] != -1)return memo[mask][num_cars];
    ll &ans = memo[mask][num_cars];

    if (mask == 0) return ans = 0;
    if (num_cars == 0) return ans = INF;
    int num_people = __builtin_popcount(mask);
    if (num_people > 5*num_cars)return INF;

    ans = INF;
    for (int ss=mask; ss; ss = (ss-1)&mask){
        if (__builtin_popcount(ss) <= 5 && __builtin_popcount(ss) > 0){
            // we try taking this subset
            ans = min(ans, max(dp(mask^ss, num_cars-1),cost_of_trip(ss)));
        }
    }
    return ans;
}
int main(){
    cin >> n >> e;
    adjmat.assign(n+2, vector<ll>(n+2, INF));
    ll u, v, w;
    for (int i=0; i<e; i++){
        cin >> u >> v >> w;
        adjmat[u][v] = min(w, adjmat[u][v]);
        adjmat[v][u] = min(w, adjmat[v][u]);
    }
    // Floyd Warshall
    for (int k=0; k<n+2; k++){
        for (int i=0; i<n+2; i++){
            for (int j=0; j<n+2; j++){
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
            }
        }
    }
    memset(memo, -1, sizeof memo);
    memset(memo2, -1, sizeof memo2);
    cout << dp((1<<n)-1, ceil(n/5.0)) << endl;
    return 0;
}