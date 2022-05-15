/**Kattis - candydistribution
 * The general cases just involve finding the modulo inverse of C mod k in the least residue class
 * (to ensure that the answer is < k). The issue is spotting the edge cases of C = 1 and K = 1. The
 * former is just about outputting k+1 unless k=1e9. The latter is about outputting 1 since after
 * processing the first case, C >= 2, so we can just have 1*(C-1) + 1 = 1*C sweets.
 * 
 * Time: O(log (min(C,K))), space: O(1).
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int mod(int a, int n) { return (a % n + n) % n; }

int extEuclid(int a, int b, int &x, int &y) {  // pass x and y by ref
    int xx = y = 0;
    int yy = x = 1;
    while (b) {  // repeats until b == 0
        int q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
}

int modInverse(int b, int m) {  // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);  // to get b*x + m*y == d
    if (d != 1) return -1;          // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return mod(x, m);
}

int num_tc;
int k, c;
int main() {
    scanf("%d", &num_tc);
    for (int tc = 0; tc < num_tc; tc++) {
        scanf("%d %d", &k, &c);
        if (c == 1) {
            if (k + 1 > (int)1e9) {
                printf("IMPOSSIBLE\n");
            } else {
                printf("%d\n", k + 1);
            }
            continue;
        }
        if (k == 1) {  // c >= 2
            printf("1\n");
            continue;
        }
        int ans = modInverse(c, k);
        if (ans == -1) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        printf("%d\n", ans);
    }
    return 0;
}
