/**Kattis - inflation
 * A fairly obvious greedy: we sort the helium tanks, assign the smallest to fill the smallest
 * balloon, second to second, etc. Assume the minimum ratio is from tank and balloon i, then if
 * we want to increase that, we would need to pair the balloon with a larger tank, but that means
 * another larger balloon will need to pair with a smaller tank :( so that will not work and by
 * a non-rigrous exchange argument, this algorithm is optimal.
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
vector<int> v;
int main() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    double ans = 1;
    bool possible = true;

    for (int i = 0; i < n; i++) {
        if (v[i] > i + 1) {
            possible = false;
            break;
        }
        ans = min(ans, (double)v[i] / (double)(i + 1));
    }
    if (possible)
        cout << fixed << setprecision(10) << ans << endl;
    else
        cout << "impossible" << endl;

    return 0;
}