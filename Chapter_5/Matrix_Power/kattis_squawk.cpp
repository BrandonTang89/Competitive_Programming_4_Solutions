/**Kattis - squawk
 * The key observation is that the number of squawks at i after t iterations is the number of t length
 * paths from s to i. After that it is just matrix exponentiation stuff.
 * 
 * Time: O(n^3 log t), Space: O(n^2)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

// O(n^3) Matrix Multiplication
vector<vector<ll>> matrix_mul(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    // (x, y), (y, z) --> (x, z)
    assert(a[0].size() == b.size()); // number of columns of a must be equal to number of rows of b
    int n = a.size(), m = b[0].size(), p = b.size(); // output n rows, m columns, p layers
    vector<vector<ll>> c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

// O(n^3 log p) Square Matrix Exponentiation
vector<vector<ll>> matrix_exp(vector<vector<ll>> &a, ll p){
    if (p == 1) return a;
    auto ans = matrix_exp(a, p/2);
    ans = matrix_mul(ans, ans);
    if (p & 1) ans = matrix_mul(ans, a);
    return ans;
}

int n, e, s, t;
vector<vector<ll>> adj_mat;
int main(){
    scanf("%d %d %d %d", &n, &e, &s, &t);
    adj_mat.assign(n, vector<ll>(n, 0));
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj_mat[u][v] = 1;
        adj_mat[v][u] = 1;
    }
    adj_mat = matrix_exp(adj_mat, t);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += adj_mat[s][i];
    }
    printf("%lld\n", ans);

}