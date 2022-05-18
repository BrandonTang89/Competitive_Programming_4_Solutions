/**Kattis - maximumrent
 * Linear programming with fixed form of constraints. We can probably solve manually, but since
 * we got library code, we just use that. Note that they want x and y to be integers rather than
 * floats, so we need to do a local search around that area (a 3x3 grid around the solution)
 * and get the best answer.
 *
 * Time: O(1), Space: O(1)
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
int a, b, m, d;
int main() {
    cin >> a >> b >> m >> d;
    vd B{-1, -1, (ld)m, (ld)-d};
    vd C{(ld)a, (ld)b};

    vvd A{{-1, 0}, {0, -1}, {1, 1}, {-2, -1}};
    vd ans;
    LPSolver solver(A, B, C);
    solver.Solve(ans);

    int cur_best = 0;
    for (int i=max(1.0, ans[0]-1); i<= ans[0]+1; i++){
        for (int j=max(1.0, ans[1]-1); j<= ans[1]+1; j++){
            if (i + j > m)continue;
            if (2*i + j < d)continue;
            cur_best = max(cur_best, a*i+b*j);
        }
    }
    cout << cur_best << endl;
}