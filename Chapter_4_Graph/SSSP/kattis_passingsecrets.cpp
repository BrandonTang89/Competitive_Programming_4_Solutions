/**Kattis - passingsecrets
 * Graph modelling dijkstra problem. The modelling is not terribly hard, we just add an extra node
 * for each group and add edges from each member to this group node (weight group_size - 1) and from
 * the group node to each member (weight 0). This ensures that the cost of using the group to pass
 * information is group_size - 1. We could do the same by making each group into a clique with
 * birectional edges of weight 0, but this is more efficient since we add less edges (2 edges per
 * group that each person is in). We then just run dijkstra from the source to the dest while
 * recording a parent vector.
 *
 * The somewhat tedious part is input parsing and converting the names to ids. It's not hard, just
 * don't mess it up. Printing the actual solution isn't too hard with the parent array, using a
 * recursive function is quite clean.
 * 
 * Time: O(E log (V+num_groups)), Space: O(V + E + num_groups)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, src, dest, num_groups;
map<string, int> name_to_id;
vector<string> id_to_name;
vector<vector<tuple<int, int>>> adjlist;  // w, v
vector<vector<string>> groups;
vector<int> dist, parent, path;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

void print_sol(int u)
{
    if (parent[u] != -1) print_sol(parent[u]);
    if (u < n) cout << id_to_name[u] << " ";
}
int main()
{
    string a, b;
    while (cin >> a >> b) {
        n = 0;
        name_to_id.clear();
        id_to_name.clear();

        if (name_to_id.find(a) == name_to_id.end()) {
            name_to_id[a] = n;
            id_to_name.push_back(a);
            n++;
        }
        if (name_to_id.find(b) == name_to_id.end()) {
            name_to_id[b] = n;
            id_to_name.push_back(b);
            n++;
        }
        assert(n == 2);
        src = name_to_id[a];
        dest = name_to_id[b];

        cin >> num_groups;
        groups.assign(num_groups, vector<string>());
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < num_groups; i++) {
            string s, line;
            getline(cin, line);
            istringstream ss(line);
            while (ss >> s) {
                groups[i].push_back(s);
                if (name_to_id.find(s) == name_to_id.end()) {
                    name_to_id[s] = n;
                    id_to_name.push_back(s);
                    n++;
                }
            }
        }

        while (!pq.empty()) pq.pop();
        dist.assign(n + num_groups, INT_MAX);
        parent.assign(n + num_groups, -1);
        adjlist.assign(n + num_groups, vector<tuple<int, int>>());
        for (int i = 0; i < num_groups; i++) {
            for (auto &v : groups[i]) {
                adjlist[name_to_id[v]].push_back({groups[i].size() - 1, n + i});
                adjlist[n + i].push_back({0, name_to_id[v]});
            }
        }

        dist[src] = 0;
        pq.emplace(0, src);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (u == dest) break;
            if (d > dist[u]) continue;  // inferior pair
            for (auto &[w, v] : adjlist[u]) {
                if (dist[u] + w >= dist[v]) continue;  // relaxing through this node doesn't help
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "impossible" << endl;
        }
        else {
            cout << dist[dest] - 1 << ' ';
            print_sol(dest);
            cout << endl;
        }
    }

    return 0;
}