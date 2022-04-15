/**Kattis - wifi
 * BSTA + greedy. Pretty straightforward, remember to sort houses first.
 * 
 * Time: O(100 * n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, m;
vector<int> houses;
bool workable(ld max_dist) {
    ld covered_until = -1;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (covered_until >= houses[i]) {
            continue;
        }
        counter++;
        covered_until = houses[i] + 2*max_dist;

        if (counter > m) {
            return false;
        }
    }
    return true;
}

int main() {
    int num_tc;
    fast_cin();
    cin >> num_tc;
    while (num_tc--) {
        cin >> m >> n;
        houses.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> houses[i];
        }
        sort(houses.begin(), houses.end());

        ld lo = 0, hi = 1e6;
        for (int i = 0; i < 50; i++) {
            ld mid = (lo + hi) / 2;
            // cout << fixed << setprecision(6) << mid << endl;
            if (workable(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        cout << fixed << setprecision(1) << hi << endl;
    }
    return 0;
}