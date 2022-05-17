/**Kattis - cheeseifyouplease
 * Simple use of simplex algorithm. Let the variables x1 .. xn be the the amount of each blend.
 * Then the constraints are such that sum of (amount of cheese i used for bland j) <= wi for
 * each cheese i.
 *
 * The objective function is (TX) where t[i] is the price of blend i, we try to maximise this. 
 * Note that X >= 0.
 * 
 * Time: O(?), Space: O(nm)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
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
int n, m;  // n variables, m constraints
int main() {
    cin >> m >> n;
    vd b(m), c(n);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vvd A(m, vd(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[j][i];
            A[j][i] /= 100;
        }
        cin >> c[i];
    }

    vd ans = vd(n);
    LPSolver solver(A, b, c);
    auto res = solver.Solve(ans);
    res = floor(res * 100.0 + 0.5 + 1e-9) / 100.0;  // round to 2 dp
    printf("%.2Lf\n", res);
}