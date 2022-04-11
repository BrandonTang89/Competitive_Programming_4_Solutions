/**Kattis - dvoniz
 * A badly worded problem. Here the term subsequence actually refers to contiguous subsequence.
 * Knowing this, for each starting i, we binary search for the k such that the range sum from
 * i to the end of the subsequence is <= 2*s and well as the sum of the first k integers of the
 * subsequence is <= s. We can do both of these at once. Then we linearly reduce k until we
 * can find a point where the last k sum to <= s. Honestly, the time complexity should be
 * O(n^2) becuase of the linear section. But its still AC so... Idk this question sucks.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, INF = 2e9, s;
vector<int> arr, ori;    // arr[i] contains the range sum from 0 to i inclusively
int rsq(int l, int r) {  // range sum from l to r inclusively
    if (l < 0 || r >= n) return 0;
    if (l > r) return 0;
    if (l == 0) return arr[r];
    return (arr[r] - arr[l - 1]);
}
int main() {
    cin >> n >> s;
    arr.resize(n);
    ori.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ori[i] = arr[i];  // only if preserving initial array
        if (i > 0) arr[i] += arr[i - 1];
    }

    for (int i = 0; i < n; i++) {
        int lo = 0, hi = (n - i) / 2;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (rsq(i, i + mid * 2 - 1) > 2 * s || rsq(i, i + mid - 1) > s)
                hi = mid - 1;
            else
                lo = mid;
        }
        if (rsq(i, i + hi * 2 - 1) > 2 * s || rsq(i, i + hi - 1) > s) hi--;

        int k = hi;
        while (true) {
            if (rsq(i + k, i + k * 2 - 1) > s)
                k--;
            else
                break;
        }
        cout << 2 * k << endl;
    }

    return 0;
}