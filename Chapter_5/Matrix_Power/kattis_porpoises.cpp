#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
const int MOD = (int) 1e9;
inline ll mod(ll a, ll b){ return (a%b+b)%b; }

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
                c[i][j] = mod(c[i][j], MOD); // Specifically for MOD
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

int main(){
    vector<vector<ll>> fib = {{1, 1}, {1, 0}};
    ll q, n;
    scanf("%lld", &q);
    for (int tc=1;tc<=q;tc++){
        scanf("%d %lld", &tc, &n);
        printf("%d %lld\n", tc, matrix_exp(fib, n)[0][1]);
    }
    return 0;
}