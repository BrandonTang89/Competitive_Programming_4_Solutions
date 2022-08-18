/**Kattis - breakingbad
 * Observe that it is possible if and only if the graph is bipartite, with each person taking each
 * partition. So we just bicolor the graph with DFS.
 * 
 * Time: O(V + E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, e;
unordered_map<string, int> m;
vector<string> items;
vector<vector<int>> adjlist;

bool isBipartite = true;
vector<int> color;
void bipartite_dfs(int u, int c) {
    if (!isBipartite) return;
    for (int v : adjlist[u]) {
        if (color[v] == -1) {
            color[v] = 1 - c;
            bipartite_dfs(v, 1 - c);
        } else if (color[v] == c) {
            isBipartite = false;
            return;
        }
    }
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        items.push_back(s);
        m[s] = i;
    }

    adjlist.assign(n, vector<int>());
    cin >> e;
    for (int i = 0; i < e; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        adjlist[m[s1]].push_back(m[s2]);
        adjlist[m[s2]].push_back(m[s1]);
    }

    color.assign(n, -1);
    for (int i = 0; i < n && isBipartite; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            bipartite_dfs(i, 0);
        }
    }

    if (isBipartite) {
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                cout << items[i] << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            if (color[i] == 1) {
                cout << items[i] << " ";
            }
        }
        cout << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}