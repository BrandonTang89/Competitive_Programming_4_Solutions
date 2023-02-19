/**Kattis - linearrecurrence
 * A question that relies on fast matrix exponentiation to determine the T-th term of a nth order
 * linear recurrence in O(n^3 log T) time. The hard part is determining the matrix to be
 * exponentiated. The invariant is that m * [1, x(i), x(i-1), ..., x(i-n+1)] = [1, x(i+1), x(i),
 * ..., x(i-n+2)]
 *
 * for the case where n == 3, m looks like
 * [[1, 0, 0, 0],
 *  [a0, a1, a2, a3],
 *  [0, 1, 0, 0],
 *  [0, 0, 1, 0]]
 *
 * Essentially the second row is the coefficients of the recurrence, and the first row [1, 0, 0,
 * 0..] all subsequent rows are 0 except for a left shifted diagonal which is 1. It is a good idea
 * to verify this yourself...
 *
 * If T < n, we can just directly produce the answer from one of the intial values. Else we have:
 * m^i * [1, x(n-1), x(n-2), ..., x(0))] = [1, x(n-1+i), x(n-2+i), ..., x(i)].
 * We first find x(t) when n-1+i == t so we set i == t-n+1 and then we return res[1][0] which
 * corresponds to the second row.
 * 
 * Time: O(n^3 log T), Space: O(n^2)
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

int MOD;
inline ll mod(ll a, ll b) { return (a % b + b) % b; }

// O(n^3) Matrix Multiplication
vector<vector<ll>> matrix_mul(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    // (x, y), (y, z) --> (x, z)
    assert(a[0].size() == b.size());  // number of columns of a must be equal to number of rows of b
    int n = a.size(), m = b[0].size(), p = b.size();  // output n rows, m columns, p layers
    vector<vector<ll>> c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] = mod(c[i][j], MOD);  // Specifically for MOD
            }
        }
    }

    return c;
}

// O(n^3 log p) Square Matrix Exponentiation
vector<vector<ll>> matrix_exp(vector<vector<ll>> &a, ll p)
{
    if (p == 1) return a;
    auto ans = matrix_exp(a, p / 2);
    ans = matrix_mul(ans, ans);
    if (p & 1) ans = matrix_mul(ans, a);
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<ll>> initial;
    vector<vector<ll>> m;
    m.assign(n + 1, vector<ll>(n + 1, 0));
    m[0][0] = 1;

    for (int i = 0; i < n + 1; i++) {
        cin >> m[1][i];
    }

    for (int i = 2; i < n + 1; i++) {
        m[i][i - 1] = 1;
    }

    initial.assign(n + 1, vector<ll>(1, 0));
    initial[0][0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> initial[n - i][0];
    }

    int q;
    cin >> q;
    while (q--) {
        ll t;
        cin >> t >> MOD;

        if (t < n) {
            cout << mod(initial[n - t][0], MOD) << endl;
        }
        else {
            auto ans = matrix_exp(m, t - n + 1);
            auto res = matrix_mul(ans, initial);
            cout << res[1][0] << endl;
        }
    }

    return 0;
}