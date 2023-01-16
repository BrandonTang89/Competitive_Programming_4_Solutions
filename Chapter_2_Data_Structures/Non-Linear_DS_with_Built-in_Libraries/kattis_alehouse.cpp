/**Kattis - alehouse
 * Somewhat sus question. The idea is that we process the people in increasing end time. For each
 * person we
 * 1. Add all people who would join by end + k time to our alehouse (a min heap of long longs).
 * These are the people who would be met by OP if he were to enter at the time of the current person
 * leaves.
 * 2. Count this number of people
 * 3. Remove all people leaving at the same time as the current person.
 *
 * The only weird corner case is when 2 people have the same start end time. we will end up
 * processing the second person after he has already left the house. But this turns out to not break
 * the algorithm since we would just count less people in the house.
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

ll n, k;
priority_queue<ll, vector<ll>, greater<ll>> house;                               // end time
priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, greater<tuple<ll, ll>>> q;  // (start, end)
vector<tuple<ll, ll>> v;                                                         // (end, start)

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        q.emplace(a, b);
        v.emplace_back(b, a);
    }
    sort(v.begin(), v.end());

    ll ans = 0;
    for (auto [end, start] : v) {
        // add all people who would join by end + k time
        while (!q.empty() && get<0>(q.top()) <= end + k) {
            auto [s, e] = q.top();
            q.pop();
            house.emplace(e);
        }

        ans = max(ans, (ll)house.size());

        // remove people who have left
        while (!house.empty() && house.top() == end) {
            house.pop();
        }
    }
    cout << ans << endl;

    return 0;
}