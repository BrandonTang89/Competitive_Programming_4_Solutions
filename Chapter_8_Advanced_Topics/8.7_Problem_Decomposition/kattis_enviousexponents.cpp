/**Kattis - enviousexponents
 * Math + Greedy. The obvious algorithm is the correct one, just "copy" the most signficant bits of
 * N and whenever there is a 0, we update our answer as the copied MSBs followed by a 1, as many 0s
 * as needed, then 1s such that the total number of 1s is k.
 *
 * There is the edge case of k > MSB(N) + 1, in which case the answer is just 2**k - 1.
 * When to stop can be non-trival to determine. obseverve that we should stop when k == 0
 * since this would make ans <= N or when k > i since this would mean we need to fit more 1s than
 * there are places for the 1s.
 *
 * Note to use the ll version of all the bit manipulation functions... Debugging issue for me
 * 
 * Time: O(log N), Mem: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    unsigned long long n, k;
    cin >> n >> k;
    unsigned long long initk = k;

    unsigned int msbi = 64 - __builtin_clzll(n) - 1;
    if (k > msbi + 1) {
        cout << (1ULL << k) - 1 << endl;
        return 0;
    }
    unsigned long long ans = 0;
    unsigned long long cur = 0;
    for (unsigned long long i = msbi + 1; i >= 0; i--) {
        if (n & (1ULL << i)) {
            k--;
            cur += (1ULL << i);
        }
        else {  // 0
            ans = cur + (1ULL << i) + (1ULL << (k - 1)) - 1;
        }
        if (k == 0 || k > i) {  // non-trival to determine
            break;
        }
    }
    assert(ans > n);
    assert(__builtin_popcountll(ans) == initk);
    cout << ans << endl;

    return 0;
}