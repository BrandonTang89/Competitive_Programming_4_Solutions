/**Kattis - euclideantsp
 * Kinda basic ternary search. Ensure you get the equation right!!
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

int n;
long double p, s, v;

long double time_taken(long double c) {
    return s * (1.0 + 1.0 / c) / v + n * (pow(log2(n), c * sqrt(2.0)) / (1e9 * p));
}
int main() {
    cin >> n >> p >> s >> v;

    long double left = 1e-12, right = 1e11;
    for (int i = 0; i < 500; i++) {
        // cout << left << " " << right << endl;
        long double mid_left = left + (right - left) / 3.0;
        long double mid_right = mid_left + (right - left) / 3.0;

        if (time_taken(mid_left) > time_taken(mid_right)) {
            left = mid_left;
        } else {
            right = mid_right;
        }
    }
    cout << fixed << setprecision(12) << time_taken(left) << " " << left << endl;

    return 0;
}