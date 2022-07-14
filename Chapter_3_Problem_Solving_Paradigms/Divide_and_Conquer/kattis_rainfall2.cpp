/**Kattis - rainfall2
 * It helps to draw the graph of the water height over time. Consider 3 cases, h < l, h == l and h >
 * l. Observe that if h < l, we should just fill up until h and then stop as leaking can never cause
 * the water level to fall below l. If h > l, we need to overfill and we must measure it when the
 * water is still leaking away. Since there is a constant leaking rate, there must be a fixed volume
 * of water when the rain stops, ie there is only 1 value of rainfall that leads to the specific h.
 * For h == l, the largest rainfall is when the height reaches l exactly when we check. This is the
 * same as the h > l case ahove. The smallest amount of rainfall is when we reach exactly l then
 * stop raining, thus only having l rainfall. 
 * 
 * We can BSTA for the rainfall amount for the case where h > l and h == l (maximum). 
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

double l, k, duration, t2, h;
const double EPS = 1e-9;

double height(double rainfall) {
    double fallrate = rainfall / duration;
    double time_to_leak = l / fallrate;
    double leak_time = t2 + (duration - time_to_leak);
    double leak_vol = leak_time * k;

    return rainfall - leak_vol;
}
int main() {
    cin >> l >> k >> duration >> t2 >> h;
    cout << fixed << setprecision(10);

    if (h + EPS < l) {
        cout << h << " " << h << endl;
        return 0;
    }

    double le = h, ri = 1e9;
    for (int i = 0; i < 100; i++) {
        double mid = (le + ri) / 2;
        if (height(mid) < h) {
            le = mid;
        } else {
            ri = mid;
        }
    }

    if (h > l + EPS) {
        cout << le << " " << le << endl;
    } else {
        cout << l << " " << ri << endl;
    }
    return 0;
}