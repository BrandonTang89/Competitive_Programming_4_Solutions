/**Kattis - shoppingmalls
 * APSP with solution. Relatively simple graph modelling question, just note that the distance
 * between floors is 5m.
 *
 * Time: O(V^3), Mem: O(V^2)
 */
#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
int n, e;
vector<int> path;
vector<vector<double>> adjmat;
vector<vector<int>> p;

// in main()
vector<tuple<int, int, int>> locs;

double inline dist(tuple<int, int, int> a, tuple<int, int, int> b)
{
    auto &[x1, y1, z1] = a;
    auto &[x2, y2, z2] = b;
    return sqrt((x1 - x2) * (x1 - x2) * 25 + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}
int main()
{
    cin >> n >> e;
    locs.resize(n);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        locs[i] = {a, b, c};
    }

    // Initialise parent matrix
    // p[i][j] is the last node before j on path i -> j
    adjmat.assign(n, vector<double>(n, INF));
    p.assign(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = i;
        }
        adjmat[i][i] = 0;
    }

    // Build Graph
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        string mode;
        cin >> mode;
        double w;
        if (mode == "walking" || mode == "stairs") {
            w = dist(locs[u], locs[v]);
            adjmat[u][v] = min(adjmat[u][v], w);
            adjmat[v][u] = min(adjmat[v][u], w);
        }
        else if (mode == "lift") {
            adjmat[u][v] = min(adjmat[u][v], 1.);
            adjmat[v][u] = min(adjmat[v][u], 1.);
        }
        else if (mode == "escalator") {
            w = dist(locs[u], locs[v]);
            adjmat[u][v] = min(adjmat[u][v], 1.);
            adjmat[v][u] = min(adjmat[v][u], 3 * w);
        }
    }

    // Actual Floyd Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjmat[i][k] + adjmat[k][j] < adjmat[i][j]) {
                    adjmat[i][j] = adjmat[i][k] + adjmat[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }

    int q;
    cin >> q;
    for (int x = 0; x < q; x++) {
        int u, v;
        cin >> u >> v;
        // Path from u -> v
        assert(adjmat[u][v] != INF);  // check if the path exist

        int cur_node = v;
        path.clear();
        while (cur_node != u) {
            path.emplace_back(cur_node);
            cur_node = p[u][cur_node];
        };
        path.emplace_back(u);
        reverse(path.begin(), path.end());

        // Print path
        for (auto x : path) {
            cout << x << " ";
        }
        cout << endl;
    }
}