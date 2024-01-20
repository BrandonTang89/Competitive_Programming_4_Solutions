/**Kattis - easyprobability
 * (easy) probability + (hard) gaussian elimination.
 * This problem was painful to say the least.. First step is to note that the 10^100 bound is so big
 * we can assume it to be infinite.
 *
 * The main idea is that we construct a system of linear equations where each variable represents
 * the state that the suffix of s matches some prefix of g or k. We let the variables x_0, x_1, ...,
 * x_n represent the probability of G winning given that the last i characters of s matches the
 * corresponding length prefix of g. We let the variables x_(n+1+0), x_(n+1+1), ..., x_(n+1+m)
 * represent the state that the last i characters of s matches the corresponding length prefix of k.
 * If some prefix of g is the same as that of k, we only use x_i rather than x_(n+1+i).
 *
 * We then use the law of total probability to construct each equation:
 * x_i = P(next matches) * x_(state if next matches) + P(next doesn't match) * x_(state if next
 * doesn't match)
 *
 * The state that matches next will usually be x_(i+1) but if the next match causes the other string
 * (k if i <= n and g if i > n) to be completed then it will be x_(n+m+1) [if k is completed] or
 * (x_n) [if g is completed].
 *
 * The state if next flip doesn't match will be computed by just finding how much of the prefix of
 * either string will match the new suffix and then take the longer one.
 *
 * The fixed points of the system will be x_n = 1 since g is finished and x_(n+m+1) = 0 since k is
 * finished.
 *
 * We now can apply gaussian elimination to solve for x_0 which is the answer.
 *
 * The issue is that floating point errors are quite significant. We cannot really use a fraction
 * library in c++ since the numerator and denominators will overflow the 64 bit integer. But luckily
 * us we can use the __float128 type which just happens to be precise enough for this to AC.
 *
 * Surprisingly, it is a significant decision to make phead a __float128 rather than a double or
 * long double, not too sure why, but it just works.
 *
 * Time: O((n+m)^3), Mem: O((n+m)^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 60;  // adjust as needed
struct AugmentedMatrix {
    __float128 mat[MAX_N][MAX_N + 1];
};
struct ColumnVector {
    __float128 vec[MAX_N];
};

ColumnVector GaussianElimination(int N, AugmentedMatrix Aug)
{
    // input: N, Augmented Matrix Aug, output: Column vector X, the answer
    for (int i = 0; i < N - 1; ++i) {  // forward elimination
        int l = i;
        for (int j = i + 1; j < N; ++j)                                    // row with max col value
            if (fabsf128(Aug.mat[j][i]) > fabsf128(Aug.mat[l][i])) l = j;  // remember this row l
        // swap this pivot row, reason: minimize floating point error
        for (int k = i; k <= N; ++k) swap(Aug.mat[i][k], Aug.mat[l][k]);
        for (int j = i + 1; j < N; ++j)  // actual fwd elimination
            for (int k = N; k >= i; --k)
                Aug.mat[j][k] -= Aug.mat[i][k] * (Aug.mat[j][i] / Aug.mat[i][i]);
    }

    ColumnVector Ans;                   // back substitution phase
    for (int j = N - 1; j >= 0; --j) {  // start from back
        double t = 0.0;
        for (int k = j + 1; k < N; ++k) t += Aug.mat[j][k] * Ans.vec[k];
        Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j];  // the answer is here
    }
    return Ans;
}

int matches(string p, string t)
{
    // how much of the suffix of p is a prefix of t
    int n = p.size();
    int m = t.size();
    int ans = 0;

    int mini = min(n, m);  // previously was n
    for (int i = 1; i <= mini; i++) {
        if (p.substr(n - i, i) == t.substr(0, i)) {
            ans = i;
        }
    }
    return ans;
}
__float128 phead;
int main()
{
    string g, k;
    long double pheadIn;
    cin >> g >> k >> pheadIn;
    phead = pheadIn;
    AugmentedMatrix A;

    int n = g.size();
    int m = k.size();
    // n + m + 2 variables

    for (int i = 0; i < n; i++) {
        // suppose the suffix of s is g[0..i)
        if (g[i] == 'H') {
            // we need to check if we get tails instead then how much of the suffix is still valid
            // as a prefix
            string suffix = g.substr(0, i);
            suffix += 'T';
            int matchg = matches(suffix, g);
            int matchk = matches(suffix, k);

            int tailVar = -1;
            if (matchg >= matchk) {
                tailVar = matchg;
            }
            else {
                tailVar = matchk + (n + 1);
            }

            int nextVar = i + 1;
            if (matches(g.substr(0, i + 1), k) == m) {
                nextVar = n + m + 1;
            }

            // x_i = phead * x_i+1 + (1-phead) * x_tailVar
            A.mat[i][i] = 1;
            A.mat[i][nextVar] += -phead;
            A.mat[i][tailVar] += -(1 - phead);
        }
        else {
            // we need to check if we get heads instead then how much of the suffix is still valid
            // as a prefix
            string suffix = g.substr(0, i);
            suffix += 'H';
            int matchg = matches(suffix, g);
            int matchk = matches(suffix, k);

            int headVar = -1;
            if (matchg >= matchk) {
                headVar = matchg;
            }
            else {
                headVar = matchk + (n + 1);
            }

            int nextVar = i + 1;
            if (matches(g.substr(0, i + 1), k) == m) {
                nextVar = n + m + 1;
            }

            // x_i = phead * x_headVar + (1-phead) * x_i+1
            A.mat[i][i] = 1;
            A.mat[i][headVar] += -phead;
            A.mat[i][nextVar] += -(1 - phead);
        }
    }
    // x_n = 1
    A.mat[n][n] = 1;
    A.mat[n][n + m + 2] = 1;

    for (int i = 0; i < m; i++) {
        string suffix = k.substr(0, i);
        int matchg = matches(suffix, g);
        if (matchg == i) {
            A.mat[n + i + 1][n + i + 1] = 1;
            continue;
        }

        if (k[i] == 'H') {
            // we need to check if we get tails instead then how much of the suffix is still valid
            // as a prefix
            suffix = k.substr(0, i);
            suffix += 'T';
            int matchg = matches(suffix, g);
            int matchk = matches(suffix, k);

            int tailVar = -1;
            if (matchg >= matchk) {
                tailVar = matchg;
            }
            else {
                tailVar = matchk + (n + 1);
            }

            int nextVar = n + i + 2;
            if (i != m - 1 && matches(k.substr(0, i + 1), g) == n) {
                nextVar = n;
            }

            // x_(n+1+i) = phead * x_(n+i+2) + (1-phead) * x_tailVar
            A.mat[n + i + 1][n + i + 1] = 1;
            A.mat[n + i + 1][nextVar] += -phead;
            A.mat[n + i + 1][tailVar] += -(1 - phead);
        }
        else {
            // we need to check if we get heads instead then how much of the suffix is still valid
            // as a prefix
            suffix = k.substr(0, i);
            suffix += 'H';
            int matchg = matches(suffix, g);
            int matchk = matches(suffix, k);

            int headVar = -1;
            if (matchg >= matchk) {
                headVar = matchg;
            }
            else {
                headVar = matchk + (n + 1);
            }

            int nextVar = n + i + 2;
            if (i != m - 1 && matches(k.substr(0, i + 1), g) == n) {
                nextVar = n;
            }

            // x_(n+1+i) = phead * headVar + (1-phead) * x_(n+i+2)
            A.mat[n + i + 1][n + i + 1] = 1;
            A.mat[n + i + 1][headVar] += -phead;
            A.mat[n + i + 1][nextVar] += -(1 - phead);
        }
    }
    A.mat[n + 1 + m][n + m + 1] = 1;
    A.mat[n + 1 + m][n + m + 2] = 0;

    ColumnVector ans = GaussianElimination(n + m + 2, A);
    assert(ans.vec[0] >= -0.0001 && ans.vec[0] <= 1.00001);
    cout << fixed << setprecision(20);
    long double sol = (long double)ans.vec[0];
    cout << sol << endl;

    return 0;
}