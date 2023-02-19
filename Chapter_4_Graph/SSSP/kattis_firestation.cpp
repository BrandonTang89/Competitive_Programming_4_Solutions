/**Kattis - firestation
 * The key design choice is to make a dummy node 0, and connect it to all firestations with weight
 * 0. To try adding a new fire station, we just need to add a new edge from 0 to the new fire
 * station. Then we run Dijkstra from 0 to every other node to get the minimum distance from each
 * node to the nearest fire station. We are trying to minimise the maximum distance from any node to
 * the nearest fire station. We can just try every node that isn't a fire station and see which one
 * gives the minimum maximum distance. 
 * 
 * Also, the input parsing is quite atypical. Remember to print a blank line after each test case.
 * 
 * Time: O(VE log V), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int tc;
int n, f;
vector<vector<tuple<int, int>>> adjlist;
vector<int> dist;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<bool> has_firestation;

int main()
{
    cin >> tc;
    while (tc--) {
        cin >> f >> n;
        adjlist.assign(n + 1, vector<tuple<int, int>>());
        has_firestation.assign(n + 1, false);
        has_firestation[0] = true;
        for (int i = 0; i < f; i++) {
            int u;
            cin >> u;
            if (has_firestation[u]) continue;  // prevent duplicates
            has_firestation[u] = true;
            adjlist[0].push_back(make_tuple(u, 0));
            adjlist[u].push_back(make_tuple(0, 0));
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;

            stringstream ss(line);
            int a, b, w;
            ss >> a >> b >> w;
            adjlist[a].push_back(make_tuple(b, w));
            adjlist[b].push_back(make_tuple(a, w));
        }

        int min_dist = INT_MAX;
        int min_firestation = 1;
        for (int i = 1; i < n + 1; i++) {
            if (has_firestation[i]) continue;

            // We try making a firestation here
            adjlist[0].push_back(make_tuple(i, 0));
            adjlist[i].push_back(make_tuple(0, 0));

            // Dijkstra from node 0
            dist.assign(n + 1, INT_MAX);
            dist[0] = 0;
            pq.push(make_pair(0, 0));
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d > dist[u]) continue;
                for (auto [v, w] : adjlist[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }

            int cur_max = 0;
            for (int j = 1; j < n + 1; j++) {
                cur_max = max(cur_max, dist[j]);
            }

            // cout << "try firestation at " << i << " with max dist " << cur_max << endl;

            if (cur_max < min_dist) {
                min_dist = cur_max;
                min_firestation = i;
            }

            // delete the firestation
            adjlist[0].pop_back();
            adjlist[i].pop_back();
        }

        cout << min_firestation << endl << endl;
    }

    return 0;
}