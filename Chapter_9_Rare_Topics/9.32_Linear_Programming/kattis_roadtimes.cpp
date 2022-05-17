/**Kattis - roadtimes
 * Floyd Warshall + Simplex Algorithm. Let the variables x1, x2, ..., xe be the time taken to
 * traverse the different edges. Di/30 >= xi >= Di/60 where Di is the length of edge i. For each
 * previously executed route, we have the added constraint that xi1+xi2+...=ti ie xi1+xi2+...<=ti
 * and xi1+xi2+...>=ti for all edges x along the shortest path between u and v. Then for each query,
 * we just maximise and minimise the edges along the shortest path between u and v.
 *
 * We find shortest paths using Floyd Warshall. Note that using long double is much slower than double,
 * and will TLE with my code.
 * 
 * Time: O(?), Space: O(e+r)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef double ld;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef vector<int> vi;

const ld EPS = 1e-9;

struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd &A, const vd &b, const vd &c)
        : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void Pivot(int r, int s) {
        double inv = 1.0 / D[r][s];
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                for (int j = 0; j < n + 2; j++)
                    if (j != s) D[i][j] -= D[r][j] * D[i][s] * inv;
        for (int j = 0; j < n + 2; j++)
            if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++)
            if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
            }
            if (D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                    ((D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]))
                    r = i;
            }
            if (r == -1) return false;
            Pivot(r, s);
        }
    }

    ld Solve(vd &x) {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -EPS) {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<ld>::infinity();
            for (int i = 0; i < m; i++)
                if (B[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s]))
                            s = j;
                    Pivot(i, s);
                }
        }
        if (!Simplex(2)) return numeric_limits<ld>::infinity();
        x = vd(n);
        for (int i = 0; i < m; i++)
            if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};
int n, e;  // n nodes, e edges (also e constraints)
vector<vector<int>> edge_index;
vvd adjmat, adjmatclosed;
map<int, pair<int, int>> inverse_edge_index;

vector<int> get_shortest_path(int u, int v) {  // get edge list of shortest path travelled
    vector<int> ans;
    while (u != v) {
        int next = -1;
        for (int i = 0; i < n; i++) {
            if (i == u) continue;
            if (fabs(adjmat[u][i] + adjmatclosed[i][v] - adjmatclosed[u][v]) < EPS) {
                next = i;
                ans.emplace_back(edge_index[u][i]);
                break;
            }
        }
        u = next;
        assert(u != -1);
    }
    return ans;
}
int main() {
    cin >> n;
    adjmat.assign(n, vector<ld>(n));
    edge_index.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adjmat[i][j];
            if (adjmat[i][j] > 0.1) {
                edge_index[i][j] = e++;
                inverse_edge_index[edge_index[i][j]] = make_pair(i, j);
            } else {
                adjmat[i][j] = (i == j ? 0 : 1e9);
            }
        }
    }
    int r;
    cin >> r;
    vvd A(2 * (r + e), vd(e));
    vd b(2 * (r + e)), c(e);
    for (int i = 0; i < e; i++) {
        A[i][i] = 1;
        auto &[u, v] = inverse_edge_index[i];
        b[i] = adjmat[u][v] * 2;  // adjmat[u][v]*60/30
    }
    for (int i = 0; i < e; i++) {
        A[e + i][i] = -1;
        auto &[u, v] = inverse_edge_index[i];
        b[e + i] = -adjmat[u][v];  // adjmat[u][v]*60/60
    }
    // Floyd warshall
    adjmatclosed = adjmat;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjmatclosed[i][j] =
                    min(adjmatclosed[i][j], adjmatclosed[i][k] + adjmatclosed[k][j]);
            }
        }
    }

    for (int i = 0; i < r; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        vi edge_list = get_shortest_path(u, v);
        for (auto x : edge_list) {
            // cout << "x " << x << endl;
            A[2 * e + i][x] = 1;
            A[2 * e + r + i][x] = -1;
        }
        b[2 * e + i] = t;
        b[2 * e + r + i] = -t;
    }
    int q;
    cout << fixed << setprecision(10);
    cin >> q;
    for (int query = 0; query < q; query++) {
        int u, v;
        vd x;
        cin >> u >> v;
        c.assign(e, 0);
        vi edge_list = get_shortest_path(u, v);

        cout << u << " " << v << ' ';
        for (auto x : edge_list) {
            c[x] = -1;
        }
        LPSolver solver(A, b, c);
        ld ans = solver.Solve(x);
        cout << -ans << " ";

        for (auto x : edge_list) {
            c[x] = 1;
        }
        LPSolver solver2(A, b, c);
        ans = solver2.Solve(x);
        cout << ans << endl;
    }
}