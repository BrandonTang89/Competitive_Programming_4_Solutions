#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

int n, m;
vector<vector<int>> adjlist;
vector<int> dist;
void dfs(int node, int d = 0) {
  if (dist[node] != -1)
    return;

  dist[node] = d;
  if (node == 0) return;

  for (int v : adjlist[node]) {
    dfs(v, d + 1);
  }
}

void solve() {
  unordered_set<int> connected_to_root;
  cin >> n >> m;

  adjlist.clear();
  adjlist.assign(n + 1, vector<int>());

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adjlist[u].push_back(v);
    adjlist[v].push_back(u);

    if (u == 0) {
      connected_to_root.insert(v);
    } else if (v == 0) {
      connected_to_root.insert(u);
    }
  }

  dist.assign(n, -1);
  dfs(n-1);

  assert(dist[0] > 0);
  int ans = dist[0];
  assert(ans > 0);
  for (int i = 0; i < m; i++) {
    int v;
    cin >> v;
    connected_to_root.insert(v - 1);
  }

  for (int v : connected_to_root) {
    if (dist[v] != -1){
      assert(v != 0);
      ans = max(ans, dist[v] + 1);
    }
  }

  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}