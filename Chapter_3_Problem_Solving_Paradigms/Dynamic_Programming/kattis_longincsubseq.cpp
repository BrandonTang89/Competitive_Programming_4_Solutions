/**Kattis -longincsubseq
 * Just the classic, print solution (but the indices rather than the actual values.)
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<int> A;  // length n
vi p;           // predecessor array

int main() {
    while (cin >> n) {
        A.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        int k = 0, lis_end = 0;
        vi L(n, 0), L_id(n, 0);
        p.assign(n, -1);

        for (int i = 0; i < n; ++i) {
            int pos = lower_bound(L.begin(), L.begin() + k, A[i]) - L.begin();
            L[pos] = A[i];                    // greedily overwrite this
            L_id[pos] = i;                    // remember the index too
            p[i] = pos ? L_id[pos - 1] : -1;  // predecessor info
            if (pos == k) {                   // can extend LIS?
                k = pos + 1;                  // k = longer LIS by +1
                lis_end = i;                  // keep best ending i
            }
        }

        cout << k << endl;
        vector<int> v;
        for (int i = lis_end; i != -1; i = p[i]) {
            v.push_back(i);
        }
        reverse(v.begin(), v.end());
        for (int i = 0; i < (int)v.size() - 1; i++) {
            cout << v[i] << " ";
        }
        cout << *--v.end() << endl;
    }

    return 0;
}
