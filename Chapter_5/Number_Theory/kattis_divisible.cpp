/**Kattis - divisible
 * Not very proud, had to look up the idea. Essentially we keep a record of the prefix sum mod n.
 * And for every new number, we compute the prefix sum from the last prefix sum + new num then check
 * the number of previous prefix sums with the same remainder. This is because for each previous
 * prefix sum with the same value as the current prefix sum, we can just take the sub array from 1
 * after the previous prefix sum until the current number. Also note to check if the prefix sum is
 * 0, in which case we can take all the numbers until current number.
 *
 * Time: O(n), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int num_tc;
int n, d;
unordered_map<int, int> m;  // m[i] is the number of prefix sums with value i
int main() {
    scanf("%d", &num_tc);
    for (int tc = 0; tc < num_tc; tc++) {
        scanf("%d %d", &d, &n);
        m.clear();

        int c, ans = 0;
        int prev = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &c);
            c += prev;
            c %= d;

            ans += m[c] + (c == 0);
            m[c]++;
            prev = c;
        }
        printf("%d\n", ans);
    }

    return 0;
}