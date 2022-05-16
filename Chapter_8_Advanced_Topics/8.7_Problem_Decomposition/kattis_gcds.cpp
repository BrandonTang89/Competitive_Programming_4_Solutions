/**Kattis - gcds
 * Notice that the range of values in A is small: [1,100]. Thus we only need to consider gcds within that range.
 * For each potential gcd, d, we check if we can find a contiguous subarray such that the gcd is d. To do so,
 * We look for contiguous blocks that are divisible by d and get the GCD of those blocks. If the GCD is d,
 * we can have d, else we continue to find more blocks.
 * 
 * Time: O(100n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<int> A;
int main() {
    int n;
    cin >> n;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int ans = 0;
    for (int d = 1; d <= 100; d++) {
        // check if there is a contiguous subarray of A with GCD = d
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            if (A[i] % d == 0) {
                int cur = A[i];
                for (; i < n; i++) {
                    cur = gcd(cur, A[i]);
                    if (cur == d) {
                        found = true;
                        break;
                    }
                    if (cur < d) {
                        i--;
                        break;
                    }
                }
            }
        }
        if (found) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}