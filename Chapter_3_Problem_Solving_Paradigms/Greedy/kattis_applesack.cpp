/**Kattis - applesack
 * Looks tough, is easy. First observe that we can assume that the guy brings all the apples to from
 * 0.5 to 1.5 first, then all from 1.5 to 2.5, etc. This is because any trips that span more than a
 * distance of 1 can be decomposed into multiple trips of length 1. Then we observe that the minimum
 * number of trips to move the apples from x to x+1 is ceil(n/k). Now observe that any arrangement
 * of apples that uses that many trips is equally good since the number of wasted slots (ceil(n/k)*k
 * - n) is the same, leading to a loss of ceil(n/k) apples. Thus can calculate the number of apples
 * at 1.5, 2.5, etc. and stop when theres 0 apples left, reporting the answer.
 *
 * Time: O(n), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
int main() {
    cin >> n >> k;
    int i;
    for (i = 1; n != 0; i++) {
        n -= (ceil(n / (double)k));
    }
    cout << i << endl;

    return 0;
}