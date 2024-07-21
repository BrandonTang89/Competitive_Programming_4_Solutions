#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
vector<vector<int>> adjlist;
vector<vector<ll>> memo; // memo[i][j] = the minimum health removed from subtree assuming the root is removed at time j
vector<ll> a; // attacking power

vector<vector<int>> children;
vector<int> visited;
int maxRounds;
void dfs(int u){ // root the tree
    visited[u] = 1;
    for (int v : adjlist[u]){
        if (!visited[v]){
            children[u].push_back(v);
            dfs(v);
        }
    }
}

ll dp(int u, int j){ 
    if (memo[u][j] != -1){
        return memo[u][j];
    }

    ll ans = a[u] * (static_cast<ll>(j+1)); // however many times u is removed

    for (int v : children[u]){
        ll best = LLONG_MAX;
        for (int k=0; k<maxRounds; k++){
            if (j == k) continue; // cannot remove at the same time
            best = min(best, dp(v, k));
        }
        ans += best;
    }

    return memo[u][j] = ans;
}
int main(){
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--){

        cin >> n;
        maxRounds = log2(n) + 5;
        a.resize(n);
        for (int i=0; i<n; i++){
            cin >> a[i];
        }

        adjlist.assign(n, vector<int>());
        for (int i=0; i<n-1; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        visited.assign(n, 0);
        children.assign(n, vector<int>());
        dfs(0); // root the tree at 0

        memo.assign(n, vector<ll>(maxRounds, -1)); // every node can be removed at time 0, 1, or 2
        ll ans = LLONG_MAX;
        for (int i=0; i<maxRounds; i++){
            ans = min(ans, dp(0, i));
        }

        cout << ans << endl;
    }

    return 0;
}