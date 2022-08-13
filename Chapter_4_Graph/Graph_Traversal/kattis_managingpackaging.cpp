/**Kattis - managingpackaging
 * We get the lexicographically smallest topological ordering, we can do this by using a custom
 * comparator in our priority queue that sorts the packages by their string name. Also we need to
 * check if this ordering even exists, by seeing if kahn's algo produces all n nodes.
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<vector<int>> adjlist;
unordered_map<string, int> m;
vector<string> words;

bool custom_comp(int a, int b) { return (words[a] > words[b]); }  // false if a comes before b

priority_queue<int, vector<int>, function<bool(int, int)>> pq(custom_comp);
int main() {
    while (true) {
        string l;
        getline(cin, l);
        n = stoi(l);
        if (n == 0) break;
        adjlist.assign(n, vi());
        m.clear();
        words.clear();
        for (int i = 0; i < n; i++) {
            string s, line;
            getline(cin, line);
            istringstream ss(line);

            string u;
            ss >> u;
            if (m.find(u) == m.end()) {
                m[u] = words.size();
                words.push_back(u);
            }
            while (ss >> s) {
                if (m.find(s) == m.end()) {
                    m[s] = words.size();
                    words.push_back(s);
                }
                adjlist[m[s]].push_back(m[u]);
            }
        }

        vector<int> in_degree(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto v : adjlist[i]) {
                in_degree[v]++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {
                pq.push(i);
            }
        }

        vector<int> ans;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            ans.push_back(u);
            for (auto v : adjlist[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    pq.push(v);
                }
            }
        }

        if ((int)ans.size() != n) {
            cout << "cannot be ordered" << endl;
        } else {
            for (int i = 0; i < n; i++) {
                cout << words[ans[i]] << endl;
            }
        }
        cout << endl;
    }

    return 0;
}