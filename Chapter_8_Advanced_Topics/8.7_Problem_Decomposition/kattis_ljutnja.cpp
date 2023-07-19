/**Kattis - ljutnja
 * Binary search + greedy + math. Not too hard, observe that we should distribute the "missing
 * candies" as evenly as possible. But how many "missing candies" should we distribute? BSTA for
 * that. What does one do with the remaining candies? We can just distribute them evenly to the
 * people who most the most candies. Greedy for that.
 *
 * Time: O(log 1e9 * n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll m, n;
vector<ll> arr;

inline ll needed(ll missing)
{
    ll candiesNeeded = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > missing) {
            candiesNeeded += arr[i] - missing;
        }
    }
    return candiesNeeded;
}
int main()
{
    fast_cin();
    cin >> m >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ll lo = 0, hi = 2e9;  // min and max number of candies requested
    // find the minimum number of missing candies such that we can distribute the rest
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (needed(mid) <= m) {
            hi = mid;
        }
        else {
            lo = mid + 1;  // need more candies
        }
    }
    assert(lo == hi);
    // cout << "missing " << lo << endl;
    // so each person has <= lo missing candies, distribute the rest max 1 extra
    ll remaining = m - needed(lo);
    ll cost = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < lo) {  // ask for less than lo, get no candies
            cost += (arr[i] * arr[i]);
        }
        else {  // >= lo, get arr[i] - lo candies
            if (remaining > 0) {
                cost += ((lo - 1) * (lo - 1));
                remaining -= 1;
            }
            else {
                cost += (lo * lo);
            }
        }
    }
    cout << cost << endl;

    return 0;
}