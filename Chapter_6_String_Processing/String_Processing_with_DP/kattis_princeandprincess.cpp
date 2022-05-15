/**Kattis - princeandprincess
 * A direct LCS problem. Note that p and q are the number of jumps and not the number of squares
 * in total.. that can cause input errors.
 * 
 * Time: O(n log k), Space: O(n)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int num_tc, n, p, q, x;
vector<int> v1, v;
int main() {
    scanf("%d", &num_tc);
    for (int tc = 1; tc <= num_tc; tc++) {
        scanf("%d %d %d", &n, &p, &q);
        p++;
        q++;
        n = n * n;
        v1.assign(n+1, 0);
        v.clear();

        for (int i = 0; i < p; i++) {
            scanf("%d", &x);
            x--;
            v1[x] = i + 1;
        }
        for (int i = 0; i < q; i++) {
            scanf("%d", &x);
            x--;
            v.push_back(v1[x]);
        }

        vector<int> L(n, 0);  // L[i] is the minimum last element of an IS of length i
        int k = 0;            // length of current LIS
        for (int i = 0; i < q; i++) {
            int pos = lower_bound(L.begin(), L.begin() + k, v[i]) - L.begin();
            L[pos] = v[i];
            if (pos == k) {
                k++;
            }
        }
        printf("Case %d: %d\n", tc, k);
    }

    return 0;
}