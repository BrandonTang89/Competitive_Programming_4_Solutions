/**Kattis - slalom2
 * Observe that we we can complete the course with vertical velocity v, we can complete it with a
 * vertical velocity < v. If we cannot complete the course with vertical velocity v, we cannot
 * complete it with any velocity > v. As such, we can binary search for v. But how do we check if a
 * specific v is viable. Observe that our possible positions for passiing through the first gate is
 * just [gates[0].first, gates[0].first + w]. Assume that we have passed through the ith gate, with
 * our most left possible position (assuming we passed all the above gates) being L and the right
 * most position being R. We can calculate the maximum horizontal distance we can travel between the
 * ith and i+1th gate by considering the time between the 2 gates. Then, we can determine the most
 * left and most right position, NL and NR that the skier can be at once he reaches the vertical
 * distance of the second gate. Now observe that we can take the intersection of the intervals [NL,
 * NR] and [gates[i+1].first, gates[i+1].first + w] as the possible positions that the skier can be
 * at passing through the i+1th gate. If the intersection is null, we conclude that it is
 * impossible. Otherwise, we can continue until we reach the nth gate.
 * 
 * Time: O(n log (1e7) + log s), Space: O(n + s)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

double EPS = 1e-9;
int w, vh, n;
vector<int> skis;

vector<pair<int, int>> gates;  // xi, yi
bool works(int v) {
    double left = gates[0].first, right = gates[0].first + w;
    for (int i = 1; i < n; i++) {
        int vert_dist = gates[i].second - gates[i - 1].second;
        double time = (double)vert_dist / v;

        double horiz_dist = time * vh;
        double nl = left - horiz_dist, nr = right + horiz_dist;

        double intersection_left = max(nl, (double)gates[i].first);
        double intersection_right = min(nr, (double)gates[i].first + w);

        if (intersection_left > intersection_right + EPS) return false;
        left = intersection_left;
        right = intersection_right;
    }
    return true;
}
int main() {
    cin >> w >> vh >> n;
    gates.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> gates[i].first >> gates[i].second;
    }

    int l = 0, r = 1e7;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (works(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (works(l)) r = l;

    int s;
    cin >> s;
    skis.resize(s);
    for (int i = 0; i < s; i++) {
        cin >> skis[i];
    }
    sort(skis.begin(), skis.end());

    int index = upper_bound(skis.begin(), skis.end(), r) - skis.begin() - 1;
    if (index < 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << skis[index] << endl;
    }

    return 0;
}