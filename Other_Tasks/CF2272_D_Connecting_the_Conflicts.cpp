#include <bits/stdc++.h>
#include <cassert>
using namespace std;

int k;
vector<vector<int>> adjlist;
vector<vector<int>> memo;
vector<int> parent;
vector<int> color;

void root(int u){
  for (int v : adjlist[u]) {
    if (v == parent[u])
      continue;
    parent[v] = u;
    root(v);
  }
}

int dp(int u, bool can_take) {
  if (memo[u][can_take] != -1)
    return memo[u][can_take];
  int res = 0;

  int res_white = 0; // answer if we don't take u
  for (int v : adjlist[u]) {
    if (v == parent[u])
      continue;
    res_white += dp(v, true);
  }

  if (!can_take) {
    res = res_white;
  } else {
    int res_black = 1; // answer if we take u
    for (int v : adjlist[u]) {
      if (v == parent[u])
        continue;
      res_black += dp(v, false);
    }
    res = max(res_white, res_black);
  }
  return memo[u][can_take] = res;
}

void opt(int u, bool can_take) {
  if (!can_take) {
    color[u] = 0; // white
    for (int v : adjlist[u]) {
      if (v == parent[u])
        continue;
      opt(v, true);
    }
    return;
  }

  int res_white = 0;
  for (int v : adjlist[u]) {
    if (v == parent[u])
      continue;
    res_white += dp(v, true);
  }

  int res_black = 1;
  for (int v : adjlist[u]) {
    if (v == parent[u])
      continue;
    res_black += dp(v, false);
  }

  if (dp(u, true) == res_white) {
    color[u] = 0; // white
    for (int v : adjlist[u]) {
      if (v == parent[u])
        continue;
      opt(v, true);
    }
  } else {
    color[u] = 1; // black
    for (int v : adjlist[u]) {
      if (v == parent[u])
        continue;
      opt(v, false);
    }
  }
}

void solve() {
  cin >> k;
  vector<int> whites(k, -1);
  for (int t = 0; t < k; t++) {
    int n;
    cin >> n;
    adjlist.assign(n, vector<int>());
    parent.assign(n, -1);
    memo.assign(n, vector<int>(2, -1));
    color.assign(n, -1);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      adjlist[u].push_back(v);
      adjlist[v].push_back(u);
    }

    root(0);
    dp(0, true);
    opt(0, true);

    auto white = std::ranges::find(color, 0);
    if (white != color.end()) {
      whites[t] = std::distance(color.begin(), white);
    }

    assert(white != color.end() || n == 1);
  }

  auto first_white =
      std::ranges::find_if(whites, [](int x) { return x != -1; });
  if (first_white == whites.end()) {
    // just join all the trees to the first tree
    for (int i = 1; i < k; i++) {
      println("{} {} {} {}", 1, 1, i + 1, 1);
    }
  } else {
    // connect everything to the first white
    int white_tree = std::distance(whites.begin(), first_white);
    int white_node = *first_white;
    for (int i = 0; i < k; i++) {
      if (i == white_tree)
        continue;
      println("{} {} {} {}", white_tree + 1, white_node + 1, i + 1, 1);
    }
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}