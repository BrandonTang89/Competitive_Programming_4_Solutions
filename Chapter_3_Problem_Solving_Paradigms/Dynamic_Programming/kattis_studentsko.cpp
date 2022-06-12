/**Kattis - studentsko
 * Relatively easy problem, just read the description properly. First we replace the skills
 * with the index of the team that the student should be in, ie the k lowest are replaced
 * with 0, the next k lowest are replaced with 1, etc. The answer is then just n - LNDS
 * of the modified array since we keep the LNDS and move the rest to their respective positions
 * one at a time.
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
int n, k;
unordered_map<int, int> m;
int main() {
    cin >> n >> k;
    vector<int> arr, v;
    arr.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        v[i] = arr[i];
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        m[v[i]] = i / k;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = m[arr[i]];
    }
    vector<int> L(n, 0);  // L[i] is the minimum last element of an IS of length i
    int k = 0;            // length of current LIS
    for (int i = 0; i < n; i++) {
        int pos = upper_bound(L.begin(), L.begin() + k, arr[i]) - L.begin();
        L[pos] = arr[i];
        if (pos == k) {
            k++;
        }
    }
    cout << n - k << endl;

    return 0;
}