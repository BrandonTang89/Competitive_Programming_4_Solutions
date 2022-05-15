/**Kattis - ones
 * A problem that I thought was hard.. So the "easy" part was reducing the problem to finding the
 * smallest i such that (10**i - 1)/9 is divisible by n, ie 10**i == 1 mod 9n. From there, I
 * throught that it would TLE to brute force try increasing i.. but apparently not so I wasted 20+
 * minutes trying to find a better solution to no avail.
 *
 * Time: O(n * ans * num_queries) which should be O(n*(n-1)*num_queries) which should TLE, but i
 * guess not
 * Space: O(1)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 1) {
            printf("1\n");
            continue;
        }
        n *= 9;
        int cur = 10, ans = 1;
        while (cur != 1) {
            cur *= 10;
            cur %= n;
            ans++;
        }
        printf("%d\n", ans);
    }

    return 0;
}