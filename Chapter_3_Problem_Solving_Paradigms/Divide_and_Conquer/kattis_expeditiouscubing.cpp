/**Kattis - expeditiouscubing
 * Just directly BSTA. Deal with rounding errors and floating point comparison.
 * 
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
double ao5(vector<double> a) {
    sort(a.begin(), a.end());
    double ans = ((double)(a[1] + a[2] + a[3])) / 3.0;
    return ans;
}
vector<double> a;
int main() {
    a.resize(5);
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    double target;
    cin >> target;

    double l = -1, r = 101, mid;
    for (int i = 0; i < 50; i++) {
        mid = (l + r) / 2.0;
        a[4] = mid;
        if (ao5(a) < target + 1e-9) { // important
            l = mid;
        } else {
            r = mid;
        }
    }

    if (l > 100) {
        cout << "infinite" << endl;
    } else if (l < 0) {
        cout << "impossible" << endl;
    } else {
        cout << fixed << setprecision(2) << l << endl; // rounding
    }

    return 0;
}