/**Kattis - equationsolver
 * Quite a tedious problem with a lot of edge cases if we don't design the code properly.
 * Just look through the code to see how I dealt with them. But the main part of the
 * check if to look for parallel lines / planes / higher dimensional lines? And if we
 * find parallel lines then we check if they are infinite or no solutions.
 * 
 * Time: O(n^3), Space: O(n^2)
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

const int MAX_N = 109;  // adjust as needed
struct AugmentedMatrix {
    double mat[MAX_N][MAX_N + 1];
};
struct ColumnVector {
    double vec[MAX_N];
};

ColumnVector GaussianElimination(int N, AugmentedMatrix Aug) {
    // input: N, Augmented Matrix Aug, output: Column vector X, the answer
    for (int i = 0; i < N - 1; ++i) {  // forward elimination
        int l = i;
        for (int j = i + 1; j < N; ++j)                            // row with max col value
            if (fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i])) l = j;  // remember this row l
        // swap this pivot row, reason: minimize floating point error
        for (int k = i; k <= N; ++k) swap(Aug.mat[i][k], Aug.mat[l][k]);
        for (int j = i + 1; j < N; ++j)  // actual fwd elimination
            for (int k = N; k >= i; --k)
                Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
    }

    ColumnVector Ans;                   // back substitution phase
    for (int j = N - 1; j >= 0; --j) {  // start from back
        double t = 0.0;
        for (int k = j + 1; k < N; ++k) t += Aug.mat[j][k] * Ans.vec[k];
        Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j];  // the answer is here
    }
    return Ans;
}

int checkSystem(int N, AugmentedMatrix Aug) {
    // input: N, Augmented Matrix Aug
    // output: 0 if system has unique solution, 1 if multiple, 2 if inconsistent

    bool multiple = false, inconsistent = false;
    for (int i = 0; i < N && !inconsistent; ++i) {
        // Check if the row is entirely 0
        bool all_zero = true;
        for (int j = 0; j < N; j++) {
            if (Aug.mat[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            if (Aug.mat[i][N] != 0)
                inconsistent = true;  // 0 != 0 is inconsistent
            else
                multiple = true;  // 0 == 0 results in inf solutions
            continue;
        }

        for (int j = i + 1; j < N && !inconsistent; ++j) {
            double factor = -1;
            bool parallel = true;
            bool set_factor = false;  // if parallel, will definitely be set since not all 0

            for (int k = 0; k < N && parallel; k++) {
                if (fabs(Aug.mat[i][k]) == 0 && fabs(Aug.mat[j][k]) == 0)
                    continue;
                
                if (fabs(Aug.mat[i][k]) == 0 || fabs(Aug.mat[j][k]) == 0) { // either 1 is 0
                    parallel = false;
                } else {
                    if (!set_factor) {
                        factor = Aug.mat[i][k] / Aug.mat[j][k];
                        set_factor = true;
                    } else {
                        if (fabs(factor - Aug.mat[i][k] / Aug.mat[j][k]) > 1e-9) {
                            parallel = false;
                        }
                    }
                }
            }

            if (!parallel) continue;
            if (fabs(factor * Aug.mat[j][N] - Aug.mat[i][N]) > 1e-9) {
                inconsistent = true;
            } else {
                multiple = true;
            }
        }
    }

    if (inconsistent) return 2;
    if (multiple) return 1;
    return 0;
}
int n;
int main() {
    cout << fixed << setprecision(10);
    while (1) {
        cin >> n;
        if (n == 0) break;
        AugmentedMatrix Aug;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> Aug.mat[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            cin >> Aug.mat[i][n];
        }
        int check = checkSystem(n, Aug);
        if (check == 2) {
            cout << "inconsistent" << endl;
        } else if (check == 1) {
            cout << "multiple" << endl;
        } else {
            ColumnVector Ans = GaussianElimination(n, Aug);
            for (int i = 0; i < n; ++i) {
                cout << Ans.vec[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}