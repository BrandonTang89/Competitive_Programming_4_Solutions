/**Kattis - familydag
 * While this looks hard initially, observe that since E < 100, the graph is definitely very small,
 * small enough to DFS from each person once. Thus, we can do the checks quite easily by seeing if
 * we can DFS from person i back to himself (paradox) or if we have 2 paths to DFS from i to u for
 * some ancestor u (hillbilly). Hardest part is honestly dealing with the input.
 *
 * Time: O(V log V + E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
map<string, int> m;
vector<string> people;
vector<vector<int>> adjlist;

bool paradox, hillbilly;
vector<int> visited;
int s;
void dfs(int u) {
    visited[u] = 1;
    for (int v : adjlist[u]) {
        if (visited[v] == 0) {
            dfs(v);
        } else if (visited[v] == 1) {
            if (v == s) {
                paradox = true;
                return;
            }
            hillbilly = true;
        }
    }
}

int main() {
    string us, dummy, vs;
    while (cin >> us) {
        if (us == "done") continue;
        cin >> dummy >> vs;
        n = 0;
        m.clear();
        people.clear();
        adjlist.clear();

        if (m.find(us) == m.end()) {
            m[us] = n++;
            people.push_back(us);
            adjlist.emplace_back(vector<int>());
        }
        if (m.find(vs) == m.end()) {
            m[vs] = n++;
            people.push_back(vs);
            adjlist.emplace_back(vector<int>());
        }

        adjlist[m[vs]].emplace_back(m[us]);

        while (true) {
            cin >> us;
            if (us == "done") break;
            cin >> dummy >> vs;
            if (m.find(us) == m.end()) {
                m[us] = n++;
                people.push_back(us);
                adjlist.emplace_back(vector<int>());
            }
            if (m.find(vs) == m.end()) {
                m[vs] = n++;
                people.push_back(vs);
                adjlist.emplace_back(vector<int>());
            }

            adjlist[m[vs]].emplace_back(m[us]);
        }

        vector<pair<string, int>> ans;
        for (int i = 0; i < n; i++) {
            visited.assign(n, 0);
            paradox = hillbilly = false;
            s = i;

            dfs(i);
            if (paradox) {
                ans.emplace_back(make_pair(people[i], -1));
            } else if (hillbilly) {
                ans.emplace_back(make_pair(people[i], 1));
            }
        }
        sort(ans.begin(), ans.end());
        for (auto &[name, type] : ans) {
            if (type == -1) {
                cout << name << " paradox" << endl;
            } else {
                cout << name << " hillbilly" << endl;
            }
        }
        cout << endl;
    }

    return 0;
}