/**Kattis - recursionrandfun
 * Here we let the state be (k, d) where the state is true iff we can have f(d) = k. Due to c
 * and b being small, we can try all possible values of RAND%b and RAND%c. Also we use the
 * "no reinitialisation" of memo trick.
 * 
 * Time: O(kdbc), Space: O(kd)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int tc = 1;
bool memo[10001][101];  // k, d
int last_filled[10001][101];
int a, b, c, d, k;

bool dp(int k, int d) {
    // cout << "k: " << k << " d: " << d << endl;
    if (k <= 0) return false;
    if (d <= 0) return (k == 1 ? true : false);  // f(d<=0) = 1
    if (last_filled[k][d] == tc) return memo[k][d];
    last_filled[k][d] = tc;

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < b; j++) {
            if (dp(k - a - j, d - 1 - i)) return memo[k][d] = true;
        }
    }

    return memo[k][d] = false;
}

int main() {
    while (cin >> a >> b >> c >> d >> k) {
        cout << (dp(k, d) ? "possible" : "impossible") << endl;
        tc++;
    }

    return 0;
}