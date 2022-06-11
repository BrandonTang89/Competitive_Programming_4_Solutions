/**Kattis - alphabet
 * easy LIS problem. Observe that 26-length of LIS gives the number of characters we need to insert
 * betweent the chars of the LIS to turn the LIS into abcdefghijklmnopqrstuvwxyz.
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

int main() {
    string v;
    cin >> v;
    int n = v.size();
    vector<int> L(n, 0);  // L[i] is the minimum last element of an IS of length i
    int k = 0;            // length of current LIS
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(L.begin(), L.begin() + k, v[i]) - L.begin();
        L[pos] = v[i];
        if (pos == k) {
            k++;
        }
    }
    cout << 26-k << endl;

    return 0;
}