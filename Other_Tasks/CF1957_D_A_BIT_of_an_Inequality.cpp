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
inline int msb(int x)
{
    return 32 - 1 - __builtin_clz(x);
}  // with the property that 2^msb(x) is the largest power of 2 <= x

vector<int> a;
vector<vector<int>> arr0, arr1;

ll q(int l, int r, int pos, int isSet)
{
    // returns the number of prefixes with last bit [l, r] that the bit of the respective position
    // is set or not set

    if (l > r) return (0);
    if (l == 0) {
        return (isSet ? arr1[r][pos] : arr0[r][pos]);
    }
    else {
        return (isSet ? arr1[r][pos] - arr1[l - 1][pos] : arr0[r][pos] - arr0[l - 1][pos]);
    }
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[i] = x;
        }

        arr0.assign(n, vector<int>(33, 0));
        arr1.assign(n, vector<int>(33, 0));

        int curPrefix = 0;
        for (int i = 0; i < n; i++) {
            curPrefix ^= a[i];

            for (int j = 0; j < 33; j++) {
                // move over previous prefixes
                arr0[i][j] = (i > 0 ? arr0[i - 1][j] : 0);
                arr1[i][j] = (i > 0 ? arr1[i - 1][j] : 0);

                // add the current prefix depending on whether the j-th bit is set
                if (curPrefix & (1 << j)) {
                    arr1[i][j]++;
                }
                else {
                    arr0[i][j]++;
                }
            }
        }

        ll ans = 0;
        for (int i=0; i<n; i++){
            int pos = msb(a[i]);
            ll res = q(i, n-1, pos, 0) * (q(0, i-1, pos, 0) + 1) + 
                     q(i, n-1, pos, 1) * q(0, i-1, pos, 1);

            ans += res;
        }
        cout << ans << endl;
    }
    return 0;
}