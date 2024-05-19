/**CF1971G
 * Simple idea which is to just do a variant of counting sort where we only sort amongst items with
 * the same x >> 2 value. Requires the reserved hash map to avoid TLE.
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

int n;
vector<int> a, b;
unordered_map<int, int[4]> d;
unordered_map<int, int> idx;

int main()
{
    fast_cin();
    d.reserve(1 << 20);
    idx.reserve(1 << 20);
    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        a.resize(n);
        b.resize(n);
        idx.clear();
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            d[a[i] >> 2][a[i] & 3]++;
        }

        for (int i = 0; i < n; i++) {
            int x = a[i];
            while (d[x >> 2][idx[x >> 2]] == 0) {
                idx[x >> 2]++;
            }
            int j = idx[x >> 2];
            d[x >> 2][j]--;
            b[i] = ((x >> 2) << 2) | j;
        }

        for (int num : b) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
