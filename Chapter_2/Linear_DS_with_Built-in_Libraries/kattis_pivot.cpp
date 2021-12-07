/**Kattis - pivot
 * Count the number of elements that could have been a pivot in quick select. This is basically
 * asking how many elements are (greater than all the elements to the left && smaller than all the
 * elements to the right). Essentially for each element, we need to know the maximum on its left
 * and the minimum on its right. If we start from the left, we can compute the maximum on the left
 * as we go. But for the minimum on the right, we should precompute it by doing a linear pass
 * from the right and for each element, update the local minimum if the current element is smaller
 * than it.
 * 
 * With these, we can do a simple linear pass to see if the element A[i] > max on left && A[i] < min 
 * on right.
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

int n, a;
vector<int> A, min_A;  // A prime
int main() {
    fast_cin();
    cin >> n;
    min_A.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a;
        A.emplace_back(a);
    }

    min_A[n - 1] = A[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        min_A[i] = min(min_A[i + 1], A[i]);
    }

    int ans = 0;
    if (min_A[1] > A[0]) ans = 1;  // check the first one
    int max_A = A[0];
    for (int i = 1; i < n - 1; i++) {
        if (A[i] > max_A && A[i] < min_A[i + 1]) ans++;
        max_A = max(max_A, A[i]);
    }
    if (A[n - 1] > max_A) ans++;

    cout << ans << endl;

    return 0;
}