/**Kattis - avoidland
 * Observe that we can handle the rows and columns separately, ie with the first test case, we need
 * to distribute the boards {1, 1, 1} and {1, 0, 2} where the first is the number of pieces in each
 * row and the second is the number of pieces in each column. We are aiming to distribute each array
 * into {1,1,1...,1}. We can do this by doing a linear pass, setting A[i] to 1 by taking or giving
 * as many as needed (A[i] - 1) from A[i+1], we record the amount of pieces moved in each step.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<int> r, c;
int main() {
    fast_cin();
    cin >> n;
    r.assign(n, 0);
    c.assign(n, 0);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        r[x - 1]++;
        c[y - 1]++;
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        r[i + 1] += r[i] - 1;
        ans += abs(r[i] - 1);

        c[i + 1] += c[i] - 1;
        ans += abs(c[i] - 1);
    }
    cout << ans << endl;

    return 0;
}