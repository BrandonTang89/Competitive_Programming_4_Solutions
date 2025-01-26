#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<vector<int>> adjlist;
vector<int> visited;
vector<int> parent;
vector<ll> r, l;
vector<pair<ll, ll>> memo; // value, totalIncrease

void rootTree(int u){
    visited[u] = 1;
    for (auto v: adjlist[u]){
        if (!visited[v]){
            parent[v] = u;
            rootTree(v);
        }
    }
}

pair<ll, ll> dp(int u){
    if (memo[u].first != -1) return memo[u];

    ll maxChildValue = 0;
    ll totalIncrease = 0;
    for (auto v: adjlist[u]){
        if (v == parent[u]) continue;
        pair<ll, ll> p = dp(v);
        maxChildValue = max(maxChildValue, p.first);
        totalIncrease += p.second;
    }
    ll thisValue = max(l[u], min(maxChildValue, r[u]));

    for (auto v: adjlist[u]){
        if (v == parent[u]) continue;
        pair<ll, ll> p = dp(v);
        totalIncrease += max(0LL, p.first - thisValue);
    }

    return memo[u] = {thisValue, totalIncrease};
}

int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        cin >> n;
        adjlist.assign(n, vector<int>());
        l.assign(n, 0);
        r.assign(n, 0);
        for (int i = 0; i < n; i++){
            cin >> l[i] >> r[i];
        }
        for (int i=0; i<n-1; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        visited.assign(n, 0);
        parent.assign(n, -1);
        rootTree(0);

        memo.assign(n, {-1, -1});
        pair<ll, ll> p = dp(0);
        cout << p.second + p.first << endl;
    }

    return 0;
}