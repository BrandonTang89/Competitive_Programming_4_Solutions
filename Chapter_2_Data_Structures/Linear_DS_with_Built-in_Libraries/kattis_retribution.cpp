/**Kattis - retribution
 * Actually simple, idk why it is 6.0 difficulty. Clearly the problems for the feather and tar are
 * identical and independent. We would like a sorted(map(dist, cartesianProduct(judges, tar))) with
 * additional information about which judge and tar is in each tuple. Then just go through the list
 * and greedily take the smallest distance that has not been taken yet, use a direct address table
 * to keep track of what judges and what tars have been taken. Do the same for the feathers. 
 * Time: O(nm' log nm'), Space: O(nm') where m' = m + p
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

int n, m, p;
vector<tuple<double, int, int>> v;  // dist, judge, loc
vector<tuple<int, int>> jud, tar, fea;
inline double dist(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
vector<int> jtaken, ttaken, ftaken;
int main()
{
    fast_cin();
    cin >> n >> m >> p;
    jud.resize(n);
    tar.resize(m);
    fea.resize(p);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        jud[i] = {x, y};
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        tar[i] = {x, y};
    }
    for (int i = 0; i < p; i++) {
        int x, y;
        cin >> x >> y;
        fea[i] = {x, y};
    }
    jtaken.assign(n, 0);
    ttaken.assign(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v.emplace_back(dist(get<0>(jud[i]), get<1>(jud[i]), get<0>(tar[j]), get<1>(tar[j])), i,
                           j);
        }
    }
    sort(v.begin(), v.end());
    double ans = 0;
    for (auto [d, i, j] : v) {
        if (!jtaken[i] && !ttaken[j]) {
            ans += d;
            jtaken[i] = 1;
            ttaken[j] = 1;
        }
    }

    jtaken.assign(n, 0);
    ftaken.assign(p, 0);
    v.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            v.emplace_back(dist(get<0>(jud[i]), get<1>(jud[i]), get<0>(fea[j]), get<1>(fea[j])), i,
                           j);
        }
    }
    sort(v.begin(), v.end());
    for (auto [d, i, j] : v) {
        if (!jtaken[i] && !ftaken[j]) {
            ans += d;
            jtaken[i] = 1;
            ftaken[j] = 1;
        }
    }

    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}