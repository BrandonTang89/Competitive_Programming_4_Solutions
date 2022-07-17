/**Kattis - svada
 * This question is lowkey confusing to solve because the number of coconuts that can be processed
 * within the time that the monkeys stay there may be greater than the actual number of coconuts
 * processed. As such, we cannot directly BSTA. Rather, we should binary search for the number of
 * coconuts that exist, checking if this results in the sum of times taken to be the total time.
 *
 * Notice that within this binary search, we need to determine the minimum time taken for each group
 * of monkeys to process k coconuts. But this is actually non-trivial. To do this, we do another
 * BSTA to determine the time taken as it is easy to verify the number of coconuts that can be eaten
 * within a certain time.
 * 
 * Time: O(log(1e9)^2 * (n + m)), Space: O(n + m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll total_time;
vector<pair<ll, ll>> a, b;

ll cp(vector<pair<ll, ll>> &v, ll time) {  // coconuts processed in time
    ll ans = 0;
    for (auto &[init, cont] : v) {
        if (time >= init) {
            ans++;
            ans += (time - init) / cont;
        }
    }
    return ans;
}
ll time_taken(vector<pair<ll, ll>> &v,
              ll coconuts) {  // min time taken to process coconuts number of coconuts
    ll l = 0, r = 1e9;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (cp(v, mid) >= coconuts) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if (cp(v, l) >= coconuts) {
        return l;
    } else {
        return r;
    }
}

int main() {
    cin >> total_time;
    int n, m;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    cin >> m;
    b.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i].first >> b[i].second;
    }
    sort(b.begin(), b.end());

    ll l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (time_taken(a, mid) + time_taken(b, mid) < total_time) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << time_taken(a, l) << endl;

    return 0;
}