/**Kattis - shopaholic
 * The optimal strategy is to group the items into groups of three greedily selecting the most
 * expensive items.
 *
 * Time: O(n log n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n;
priority_queue<ll> pq;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pq.push(x);
    }
    ll ans = 0;
    int counter = 0;
    while (!pq.empty()) {
        // Add every third element to answer
        if (counter == 2) {
            ans += pq.top();
            pq.pop();
            counter = 0;
        } else {
            pq.pop();
            counter++;
        }
    }
    cout << ans << endl;

    return 0;
}