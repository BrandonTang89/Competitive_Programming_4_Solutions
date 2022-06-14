/**Kattis - grass
 * classic interval covering problem. Sort by increasing left and decreasing right boundaries. Then
 * we take the one that covers the most right while still joining with the previously covered place.
 * This is a linear pass.
 *
 * Note that we need to check if a sprinkler can even cover any amount of grass, eliminate useless
 * sprinklers before anything else.
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

vector<pair<double, double>> sprinkers;
bool cmp(
    pair<double, double> a,
    pair<double, double> b) {  // sort by increasing left border then by decreasing right border
    if (a.first < b.first) return true;
    if (a.first > b.first) return false;
    return a.second > b.second;
}

int n;
double l, w, EPS = 1e-9;
int main() {
    fast_cin();
    while (cin >> n >> l >> w) {
        sprinkers.clear();
        for (int i = 0; i < n; i++) {
            double c, r;
            cin >> c >> r;
            double x = r * r - (w / 2.0) * (w / 2.0);
            if (x < 0) continue;  // Useless sprinkler
            sprinkers.push_back(make_pair(c - sqrt(x), c + sqrt(x)));
        }

        sort(sprinkers.begin(), sprinkers.end(), cmp);
        n = sprinkers.size();
        bool possible = true;
        double covered = 0;
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (covered + EPS > l) break;
            if (sprinkers[i].second < covered + EPS) continue;  // already covered
            if (sprinkers[i].first > covered + EPS) {
                possible = false;
                break;
            }
            double max_r = -1.0;
            int max_id = i;
            for (int j = i; j < n && (sprinkers[j].first < covered + EPS); j++) {
                if (sprinkers[j].second > max_r) {
                    max_r = sprinkers[j].second;
                    max_id = j;
                }
            }
            ans++;
            covered = max_r;
            i = max_id;
        }
        if (!possible || covered < l)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }

    return 0;
}